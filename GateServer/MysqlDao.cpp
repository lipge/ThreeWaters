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

		// ����_polSize������
		for (int i = 0; i < _polSize; i++) {
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
			auto* con = driver->connect(_url, _user, _pass);
			con->setSchema(_schema);
			// ��ȡ��ǰʱ���
			auto currentTime = std::chrono::system_clock::now().time_since_epoch();
			// ��ʱ���ת��Ϊ��
			int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();

			_pool.push(std::make_unique<SqlConnection>(con, timestamp));

		}
		_check_thread = std::thread([this]() {
			// whileѭ�� �����߳� ��detach���ɲ���ϵͳ�����߳�
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
	// 1.����
	std::lock_guard<std::mutex> guard(_mutex);

	// 2.��ȡ��ǰ���д�С
	int poolsize = _pool.size();
	// ��ȡ��ǰʱ���
	auto currentTime = std::chrono::system_clock::now().time_since_epoch();
	// ��ʱ���ת��Ϊ��
	int64_t timestamp = std::chrono::duration_cast<std::chrono::seconds>(currentTime).count();

	for (int i = 0; i < poolsize; i++) {
		auto con = std::move(_pool.front());
		_pool.pop();
		// ����}��ִ�����lambda���ʽ
		Defer tempDerfer([this, &con]() {

			_pool.push(std::move(con));

			});
		// �������ʱ��С��5��
		if (timestamp - con->_last_oper_time < 5) {
			continue;
		}

		try {
			std::unique_ptr<sql::Statement> stmt(con->_con->createStatement());
			stmt->executeQuery("SELECT 1");		// ���ִ��һ�β�ѯ����ֹ�Ͽ�����
			con->_last_oper_time = timestamp;
		}
		catch (sql::SQLException& e) {
			std::cerr << "Error keeping connection alive: " << e.what() << std::endl;
			sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

			auto newcon = driver->connect(_url, _user, _pass);	// ����������
			newcon->setSchema(_schema);							// ������ѡ�����ݿ�
			con->_con.reset(newcon);							// ����������Ϊ������
			con->_last_oper_time = timestamp;
		}
	}
}

std::unique_ptr<SqlConnection> MysqlPool::getConn()
{
	std::unique_lock<std::mutex> lock(_mutex);
	// �ȴ������������ѣ��ڶ����������Ϊtrue������ִ�У�false�����ȴ�
	_cond.wait(lock, [this]() {
		// ���Ѻ��ж��Ƿ�Ӧ��ֹͣ
		if (_b_stop) {
			return true;
		}
		// ���Ѻ��ж����ӳ��Ƿ������� �� �Ƿ�Ϊ�գ�Ϊ�շ���false
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

// �������ã���������
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

//ע���û�
int MysqlDao::RegUser(const std::string& name, const std::string& email, const std::string& pwd, const std::string& icon)
{
	auto con = _sqlpool->getConn();
	try {
		if (con == nullptr) {
			return false;
		}
		// 1.׼�����ô洢����
		std::unique_ptr < sql::PreparedStatement > stmt(con->_con->prepareStatement("CALL reg_user(?,?,?,?,@result)"));
		// 2.�����������
		stmt->setString(1, name);
		stmt->setString(2, email);
		stmt->setString(3, pwd);
		stmt->setString(4, icon);
		// 3.ִ�д洢����
		stmt->execute();

		// ��ʹ�ڵ��߳��߼��ķ����������У����� SQL ����ִ����洢�����ڹ�����û�б������𣬵��洢���������ܡ�������֯������������
		// ����sql��乹�ɵĴ洢���̻ᱻԤ���룬�����ֻ��Ҫ���ã��ң�ִ��һ��ֻ��Ҫһ��getconnection����������ִ����Ҫ���
		// ����PreparedStatement��ֱ��֧��ע�����������������Ҫʹ�ûỰ������������������ȡ���������ֵ
		// ����洢���������˻Ự��������������ʽ��ȡ���������ֵ�������������ִ��SELECT��ѯ����ȡ����
		// ���磬����洢����������һ���Ự����@result���洢������������������ȡ��
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
// ��������Ƿ����
bool MysqlDao::CheckEmail(const std::string& name, const std::string& email)
{
	auto con = _sqlpool->getConn();
	if (con == nullptr) {
		return false;
	}

	try {

		// ׼����ѯ���
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT `email` FROM user WHERE name = ?"));
		pstmt->setString(1, name);
		// ִ�в�ѯ
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		// ���������
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
// ��������
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
		std::cout << updateCnt << " ����Ӱ��" << std::endl;
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
		// ׼����ѯ���
		std::unique_ptr<sql::PreparedStatement> pstmt(con->_con->prepareStatement("SELECT * FROM user WHERE `email` = ?"));
		pstmt->setString(1, email);
		// ִ�в�ѯ
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
		// ���������
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
		// �״������û�uid��ͨ�����ݿ�uid�ֶ���������
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
