#include "MysqlDao.h"
#include "ConfigMgr.h"


MysqlPool::MysqlPool(const std::string& url, const std::string& user, const std::string& pass, const std::string& schema, int poolsize)
	:_url(url),
	_user(user),
	_pass(pass),
	_schema(schema),
	_polSize(poolsize),
	_b_stop(false)
{
	try {

		// 创建_polSize个连接
		for (int i = 0; i < _polSize; i++) {
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
			auto* con = driver->connect(_url, _user, _pass);
			con->setSchema(_schema);
			// 获取当前时间戳
			auto currentTime = std::chrono::system_clock::now().time_since_epoch();
			// 将时间戳转换为秒
			int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();

			_pool.push(std::make_unique<SqlConnection>(con, timestamp));

		}
		_check_thread = std::thread([this]() {
			// while循环 单独线程 且detach交由操作系统回收线程
			while (!_b_stop) {
				checkConnection();
				std::this_thread::sleep_for(std::chrono::seconds(60));
			}
			});
		_check_thread.detach();
	}
	catch (sql::SQLException& e) {
		std::cerr << "MysqlPool init failed: " << e.what() << std::endl;
	}
}

void MysqlPool::checkConnection()
{
	// 1.加锁
	std::lock_guard<std::mutex> guard(_mutex);

	// 2.获取当前队列大小
	int poolsize = _pool.size();
	// 获取当前时间戳
	auto currentTime = std::chrono::system_clock::now().time_since_epoch();
	// 将时间戳转换为秒
	int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();

	for (int i = 0; i < poolsize; i++) {
		auto con = std::move(_pool.front());
		_pool.pop();
		// 遇到}会执行这个lambda表达式
		Defer tempDerfer([this, &con]() {

			_pool.push(std::move(con));

			});
		// 出队入队时间小于5秒
		if (timestamp - con->_last_oper_time < 5) {
			continue;
		}

		try {
			std::unique_ptr<sql::Statement> stmt(con->_con->createStatement());
			stmt->executeQuery("SELECT 1");		// 随便执行一次查询，防止断开连接
			con->_last_oper_time = timestamp;
		}
		catch (sql::SQLException& e) {
			std::cerr << "Error keeping connection alive: " << e.what() << std::endl;
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

			auto newcon = driver->connect(_url, _user, _pass);	// 生成新连接
			newcon->setSchema(_schema);							// 新连接选择数据库
			con->_con.reset(newcon);							// 旧连接设置为新连接
			con->_last_oper_time = timestamp;
		}
	}
}

std::unique_ptr<SqlConnection> MysqlPool::getConn()
{
	std::unique_lock<std::mutex> lock(_mutex);
	// 等待条件变量唤醒，第二个参数如果为true则往下执行，false继续等待
	_cond.wait(lock, [this]() {
		// 唤醒后判断是否应该停止
		if (_b_stop) {
			return true;
		}
		// 唤醒后判断连接池是否有连接 即 是否为空，为空返回false
		return !_pool.empty();
		});
	if (_b_stop) {
		return nullptr;
	}
	std::unique_ptr<SqlConnection> con(std::move(_pool.front()));
	_pool.pop();
	return con;
}

void MysqlPool::returnConn(std::unique_ptr<SqlConnection> con)
{
	std::unique_lock<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_pool.push(std::move(con));
	_cond.notify_one();

}

void MysqlPool::Close()
{
	_b_stop = true;
	_cond.notify_all();
}

MysqlPool::~MysqlPool()
{
	std::unique_lock<std::mutex> lock(_mutex);
	while (!_pool.empty()) {
		_pool.pop();
	}
}

// 导入配置，创建连接
MysqlDao::MysqlDao()
{
	auto& cfg = ConfigMgr::GetInstance();
	const auto& host = cfg["Mysql"]["Host"];
	const auto& port = cfg["Mysql"]["Port"];
	const auto& pwd = cfg["Mysql"]["Passwd"];
	const auto& schema = cfg["Mysql"]["Schema"];
	const auto& user = cfg["Mysql"]["User"];
	_sqlpool.reset(new MysqlPool(host + ":" + port, user, pwd, schema, 3));
}

MysqlDao::~MysqlDao()
{
	_sqlpool->Close();
}

//注册用户
int MysqlDao::RegUser(const std::string& name, const std::string& email, const std::string& pwd, const std::string& icon)
{
	auto con = _sqlpool->getConn();
	try {
		if (con == nullptr) {
			return false;
		}
		// 1.准备调用存储过程
		std::unique_ptr < sql::PreparedStatement > stmt(con->_con->prepareStatement("CALL reg_user(?,?,?,?,@result)"));
		// 2.设置输入参数
		stmt->setString(1, name);
		stmt->setString(2, email);
		stmt->setString(3, pwd);
		stmt->setString(4, icon);
		// 3.执行存储过程
		stmt->execute();

		// 即使在单线程逻辑的服务器环境中，逐条 SQL 语句的执行与存储过程在功能上没有本质区别，但存储过程在性能、代码组织方面仍有优势
		// 多条sql语句构成的存储过程会被预编译，服务端只需要调用，且，执行一次只需要一次getconnection操作，逐条执行需要多次
		// 由于PreparedStatement不直接支持注册输出参数，我们需要使用会话变量或其他方法来获取输出参数的值
		// 如果存储过程设置了会话变量或有其他方式获取输出参数的值，你可以在这里执行SELECT查询来获取它们
		// 例如，如果存储过程设置了一个会话变量@result来存储输出结果，可以这样获取：
		std::unique_ptr<sql::Statement> stmtResult(con->_con->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result AS result"));
		if (res->next()) {
			int result = res->getInt("result");
			std::cout << "Result: " << result << std::endl;
			_sqlpool->returnConn(std::move(con));
			return result;
		}
		_sqlpool->returnConn(std::move(con));
		return -1;
	}
	catch (sql::SQLException& e) {
		_sqlpool->returnConn(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return -1;
	}
}
// 检查邮箱是否存在
bool MysqlDao::CheckEmail(const std::string& name, const std::string& email)
{
	auto con = _sqlpool->getConn();
	if (con == nullptr) {
		return false;
	}

	try {

		// 准备查询语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT `email` FROM user WHERE name = ?"));
		pstmt->setString(1, name);
		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		// 遍历结果集
		while (res->next()) {
			std::cout << "Check Email: " << res->getString("email") << std::endl;
			if (email != res->getString("email")) {
				_sqlpool->returnConn(std::move(con));
				return false;
			}
		}
		_sqlpool->returnConn(std::move(con));
		return true;

	}
	catch (sql::SQLException& e) {
		_sqlpool->returnConn(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}
// 更新密码
bool MysqlDao::UpdatePwd(const std::string& email, const std::string& pwd)
{
	auto con = _sqlpool->getConn();
	if (con == nullptr) {
		return false;
	}

	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("UPDATE user SET pwd=? WHERE email=?"));
		pstmt->setString(1, pwd);
		pstmt->setString(2, email);

		int updateCnt = pstmt->executeUpdate();
		std::cout << updateCnt << " 行受影响" << std::endl;
		_sqlpool->returnConn(std::move(con));
		return true;
	}
	catch (sql::SQLException& e) {
		_sqlpool->returnConn(std::move(con));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}

}

bool MysqlDao::CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo)
{
	auto con = _sqlpool->getConn();
	if (con == nullptr) {
		return false;
	}

	Defer defer([this, &con]() {
		_sqlpool->returnConn(std::move(con));
		});

	try {
		// 准备查询语句
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE `email` = ?"));
		pstmt->setString(1, email);
		// 执行查询
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		// 遍历结果集
		std::string dbPwd = "";
		while (res->next()) {
			dbPwd = res->getString("pwd");
			std::cout << "Check Pwd: " << dbPwd << std::endl;
			break;
		}
		int length = dbPwd.length() % 255;

		if (pwd != dbPwd) {

			return false;
		}
		// 首次设置用户uid，通过数据库uid字段自增生成
		userInfo.name = res->getString("name");
		userInfo.email = res->getString("email");
		userInfo.uid = res->getInt("uid");
		userInfo.pwd = dbPwd;

		return true;
	}
	catch (sql::SQLException& e) {

		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
}
