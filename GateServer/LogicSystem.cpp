#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifygRPCClient.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"
#include "StatusGrpcClient.h"
// LogicSystem构造函数
LogicSystem::LogicSystem()
{
	// 这里是函数体
	// 使用的map的key值来区分不同函数指针

	// 注册get_test测试函数
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {

		beast::ostream(connection->_response.body()) << "Receive get_text req";

		// 处理请求
		int i = 0;
		for (auto& elem : connection->_get_params) {
			i++;
			beast::ostream(connection->_response.body()) << "param" << i << "key= " << elem.first;
			beast::ostream(connection->_response.body()) << "param" << i << "value= " << elem.second << std::endl;
		}

		});

	// 注册get_varifycode获取验证码函数
	
	RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "Receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;        // 解析器
		Json::Value src_root;       // 源内容

		bool parse_success = reader.parse(body_str, src_root);          // 解析到src_root中
		if (!parse_success) {                                           // 1.解析失败的话，返回
			std::cout << "Failed to parse JSON!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr << std::endl;
			return;
		}

		if (!src_root.isMember("email")) {                      // 2.发送来的源json内容中不含email字段，返回
			std::cout << "Key is not exist!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr << std::endl;
			return;
		}

		auto email = src_root["email"].asString();          // 邮箱
		// 在这里，调用grpc 获取验证码服务
		GetVarifyRsp rsp = VerifygRPCClient::GetInstance()->GetVarifyCode(email);

		std::cout << "Email is " << email << std::endl;
		root["error"] = rsp.error();
		root["email"] = src_root["email"];
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr << std::endl;// 写入到响应体
		return;

		});

	// 发送完验证码，确认验证码的逻辑，判断用户输入的验证码，与Redis中的验证码是否匹配，匹配则用户注册成功
	// 用户点击了发送验证码，这个函数需要向Redis发起GET读请求，通过key值，即用户信息，获取存储在Redis中的验证码，这个验证码是nodejs的获取验证码服务写进去的
	RegPost("/user_register", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// 1.先查找redis中是否存在key值email
		std::string  varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
		if (!b_get_varify) {                                            // 向Redis发送请求，GET结果返回0，说明邮箱不存在，超过了字段设置的过期时间
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;                  // 验证码过期
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// 
		auto email = src_root["email"].asString();          // 邮箱
		auto name = src_root["user"].asString();            // 用户名
		auto pwd = src_root["passwd"].asString();           // 密码
		auto confirm = src_root["confirm"].asString();      // 确认密码
		auto icon = src_root["icon"].asString();			// 随机头像

		// 2.判断二次输入的密码是否一致
		if (pwd != confirm) {                               // 注册时二次输入密码不一致
			std::cout << "passwd err" << std::endl;
			root["error"] = ErrorCodes::PasswdErr;
			std::string jsonstr = root.toStyledString();    // 要发送的内容序列化成字符串
			beast::ostream(connection->_response.body()) << jsonstr;// 写入到回应请求
			return;
		}

		// 3.判断输入的验证码与Redis中的验证码是否一致，Redis中的验证码是随机生成，由VarifyServer存入，以Redis中为准
		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << " varify code error" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;                  // 验证码错误
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// 查找数据库判断用户是否存在、邮箱是否存在
		int uid = MysqlMgr::GetInstance()->RegUser(name, email, pwd, icon);
		if (uid == 0 || uid == -1) {
			std::cerr << "User or Email exist" << std::endl;
			root["error"] = ErrorCodes::UserExist;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}


		root["error"] = 0;
		root["email"] = email;
		root["uid"] = std::to_string(uid);
		root["user"] = name;
		root["passwd"] = pwd;
		root["confirm"] = confirm;
		root["varifycode"] = src_root["varifycode"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;                // 将json序列化内容写入响应体
		return;
		});

	// 重置密码Post请求
	RegPost("/reset_pwd", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		auto email = src_root["email"].asString();          // 邮箱
		auto name = src_root["user"].asString();            // 用户名
		auto pwd = src_root["passwd"].asString();           // 密码
		// 1.查找redis中是否存在key值email，再根据email取出验证码
		std::string  varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
		if (!b_get_varify) {                                            // 向Redis发送请求，GET结果返回0，说明邮箱不存在，超过了字段设置的过期时间
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;                  // 验证码过期
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}
		// 2.判断输入的验证码与Redis中的验证码是否一致，Redis中的验证码是随机生成，由VarifyServer存入，以Redis中为准
		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << " varify code error" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;                  // 验证码错误
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// 查找数据库判断用户/邮箱是否匹配
		bool match = MysqlMgr::GetInstance()->CheckEmail(name, email);
		if (!match) {
			std::cerr << "User Email Not Match" << std::endl;
			root["error"] = ErrorCodes::EmailNotMatch;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// 更新密码
		bool update_ok = MysqlMgr::GetInstance()->UpdatePwd(email, pwd);
		if (!update_ok) {
			std::cerr << "Update Passwd Failed" << std::endl;
			root["error"] = ErrorCodes::PasswdUpFailed;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		root["error"] = 0;
		root["email"] = email;
		root["user"] = name;
		root["passwd"] = pwd;
		root["varifycode"] = src_root["varifycode"].asString();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;                // 将json序列化内容写入响应体
		std::cout << "Success Update Passwd" << std::endl;
		return;
		});



	// 登录逻辑，根据邮箱与密码判断
	RegPost("/user_login", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "Receive Body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// 
		auto email = src_root["email"].asString();          // 邮箱
		auto pwd = src_root["passwd"].asString();           // 密码
		UserInfo userInfo;

		// 查找数据库判断邮箱密码是否匹配
		bool pwd_match = MysqlMgr::GetInstance()->CheckPwd(email, pwd, userInfo);
		if (!pwd_match) {
			std::cerr << "Email Pwd not Match" << std::endl;
			root["error"] = ErrorCodes::PasswdErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}
		// 查询StatusServer找到合适的连接
		auto reply = StatusGrpcClient::GetInstance()->GetChatServer(userInfo.uid);
		if (reply.error() == ErrorCodes::RPCFailed) {
			std::cerr << "Grpc Getchatserver Failed" << std::endl;
			root["error"] = ErrorCodes::RPCFailed;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		root["error"] = 0;
		root["email"] = email;
		root["uid"] = userInfo.uid;
		std::cout << "用户Uid: " << userInfo.uid << std::endl;
		std::cout << "服务器token: " << reply.token() << std::endl;
		// 客户端将要连接的服务端的信息
		root["token"] = reply.token();
		root["host"] = reply.host();
		root["port"] = reply.port();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;                // 将json序列化内容写入响应体
		return;
		});
}

// 注册Get请求
void LogicSystem::RegGet(std::string url, HttpHandler reg_handler)
{
	//    std::cout << "RegGet Create " << std::endl;
	_get_handlers[url] = reg_handler;
}


// 注册POST请求
void LogicSystem::RegPost(std::string url, HttpHandler reg_handler)
{
	//    std::cout << "RegGet Create " << std::endl;
	_post_handlers[url] = reg_handler;
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> connection)
{
	// 请求的URL不在map中，自然，不会有相应的处理函数
	if (_get_handlers.find(path) == _get_handlers.end()) {
		return false;
	}

	// 函数名：_get_handlers[path]()
	// 参数connection
	// 函数体：见LogicSystem构造函数RegGet lambda表达式
	_get_handlers[path](connection);
	return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> connection)
{
	// 请求的URL不在map中，自然，不会有相应的处理函数
	if (_post_handlers.find(path) == _post_handlers.end()) {
		return false;
	}

	// 函数名：_get_handlers[path]()
	// 参数connection
	// 函数体：见LogicSystem构造函数RegGet lambda表达式
	_post_handlers[path](connection);
	return true;
}




LogicSystem::~LogicSystem()
{
}
