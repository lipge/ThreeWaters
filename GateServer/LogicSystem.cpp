#include "LogicSystem.h"
#include "HttpConnection.h"
#include "VerifygRPCClient.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"
#include "StatusGrpcClient.h"
// LogicSystem���캯��
LogicSystem::LogicSystem()
{
	// �����Ǻ�����
	// ʹ�õ�map��keyֵ�����ֲ�ͬ����ָ��

	// ע��get_test���Ժ���
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {

		beast::ostream(connection->_response.body()) << "Receive get_text req";

		// ��������
		int i = 0;
		for (auto& elem : connection->_get_params) {
			i++;
			beast::ostream(connection->_response.body()) << "param" << i << "key= " << elem.first;
			beast::ostream(connection->_response.body()) << "param" << i << "value= " << elem.second << std::endl;
		}

		});

	// ע��get_varifycode��ȡ��֤�뺯��
	
	RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = boost::beast::buffers_to_string(connection->_request.body().data());
		std::cout << "Receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;        // ������
		Json::Value src_root;       // Դ����

		bool parse_success = reader.parse(body_str, src_root);          // ������src_root��
		if (!parse_success) {                                           // 1.����ʧ�ܵĻ�������
			std::cout << "Failed to parse JSON!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr << std::endl;
			return;
		}

		if (!src_root.isMember("email")) {                      // 2.��������Դjson�����в���email�ֶΣ�����
			std::cout << "Key is not exist!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr << std::endl;
			return;
		}

		auto email = src_root["email"].asString();          // ����
		// ���������grpc ��ȡ��֤�����
		GetVarifyRsp rsp = VerifygRPCClient::GetInstance()->GetVarifyCode(email);

		std::cout << "Email is " << email << std::endl;
		root["error"] = rsp.error();
		root["email"] = src_root["email"];
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr << std::endl;// д�뵽��Ӧ��
		return;

		});

	// ��������֤�룬ȷ����֤����߼����ж��û��������֤�룬��Redis�е���֤���Ƿ�ƥ�䣬ƥ�����û�ע��ɹ�
	// �û�����˷�����֤�룬���������Ҫ��Redis����GET������ͨ��keyֵ�����û���Ϣ����ȡ�洢��Redis�е���֤�룬�����֤����nodejs�Ļ�ȡ��֤�����д��ȥ��
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

		// 1.�Ȳ���redis���Ƿ����keyֵemail
		std::string  varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
		if (!b_get_varify) {                                            // ��Redis��������GET�������0��˵�����䲻���ڣ��������ֶ����õĹ���ʱ��
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;                  // ��֤�����
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// 
		auto email = src_root["email"].asString();          // ����
		auto name = src_root["user"].asString();            // �û���
		auto pwd = src_root["passwd"].asString();           // ����
		auto confirm = src_root["confirm"].asString();      // ȷ������
		auto icon = src_root["icon"].asString();			// ���ͷ��

		// 2.�ж϶�������������Ƿ�һ��
		if (pwd != confirm) {                               // ע��ʱ�����������벻һ��
			std::cout << "passwd err" << std::endl;
			root["error"] = ErrorCodes::PasswdErr;
			std::string jsonstr = root.toStyledString();    // Ҫ���͵��������л����ַ���
			beast::ostream(connection->_response.body()) << jsonstr;// д�뵽��Ӧ����
			return;
		}

		// 3.�ж��������֤����Redis�е���֤���Ƿ�һ�£�Redis�е���֤����������ɣ���VarifyServer���룬��Redis��Ϊ׼
		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << " varify code error" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;                  // ��֤�����
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// �������ݿ��ж��û��Ƿ���ڡ������Ƿ����
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
		beast::ostream(connection->_response.body()) << jsonstr;                // ��json���л�����д����Ӧ��
		return;
		});

	// ��������Post����
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

		auto email = src_root["email"].asString();          // ����
		auto name = src_root["user"].asString();            // �û���
		auto pwd = src_root["passwd"].asString();           // ����
		// 1.����redis���Ƿ����keyֵemail���ٸ���emailȡ����֤��
		std::string  varify_code;
		bool b_get_varify = RedisMgr::GetInstance()->Get(CODEPREFIX + src_root["email"].asString(), varify_code);
		if (!b_get_varify) {                                            // ��Redis��������GET�������0��˵�����䲻���ڣ��������ֶ����õĹ���ʱ��
			std::cout << " get varify code expired" << std::endl;
			root["error"] = ErrorCodes::VarifyExpired;                  // ��֤�����
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}
		// 2.�ж��������֤����Redis�е���֤���Ƿ�һ�£�Redis�е���֤����������ɣ���VarifyServer���룬��Redis��Ϊ׼
		if (varify_code != src_root["varifycode"].asString()) {
			std::cout << " varify code error" << std::endl;
			root["error"] = ErrorCodes::VarifyCodeErr;                  // ��֤�����
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// �������ݿ��ж��û�/�����Ƿ�ƥ��
		bool match = MysqlMgr::GetInstance()->CheckEmail(name, email);
		if (!match) {
			std::cerr << "User Email Not Match" << std::endl;
			root["error"] = ErrorCodes::EmailNotMatch;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}

		// ��������
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
		beast::ostream(connection->_response.body()) << jsonstr;                // ��json���л�����д����Ӧ��
		std::cout << "Success Update Passwd" << std::endl;
		return;
		});



	// ��¼�߼������������������ж�
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
		auto email = src_root["email"].asString();          // ����
		auto pwd = src_root["passwd"].asString();           // ����
		UserInfo userInfo;

		// �������ݿ��ж����������Ƿ�ƥ��
		bool pwd_match = MysqlMgr::GetInstance()->CheckPwd(email, pwd, userInfo);
		if (!pwd_match) {
			std::cerr << "Email Pwd not Match" << std::endl;
			root["error"] = ErrorCodes::PasswdErr;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return;
		}
		// ��ѯStatusServer�ҵ����ʵ�����
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
		std::cout << "�û�Uid: " << userInfo.uid << std::endl;
		std::cout << "������token: " << reply.token() << std::endl;
		// �ͻ��˽�Ҫ���ӵķ���˵���Ϣ
		root["token"] = reply.token();
		root["host"] = reply.host();
		root["port"] = reply.port();
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;                // ��json���л�����д����Ӧ��
		return;
		});
}

// ע��Get����
void LogicSystem::RegGet(std::string url, HttpHandler reg_handler)
{
	//    std::cout << "RegGet Create " << std::endl;
	_get_handlers[url] = reg_handler;
}


// ע��POST����
void LogicSystem::RegPost(std::string url, HttpHandler reg_handler)
{
	//    std::cout << "RegGet Create " << std::endl;
	_post_handlers[url] = reg_handler;
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> connection)
{
	// �����URL����map�У���Ȼ����������Ӧ�Ĵ�����
	if (_get_handlers.find(path) == _get_handlers.end()) {
		return false;
	}

	// ��������_get_handlers[path]()
	// ����connection
	// �����壺��LogicSystem���캯��RegGet lambda���ʽ
	_get_handlers[path](connection);
	return true;
}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> connection)
{
	// �����URL����map�У���Ȼ����������Ӧ�Ĵ�����
	if (_post_handlers.find(path) == _post_handlers.end()) {
		return false;
	}

	// ��������_get_handlers[path]()
	// ����connection
	// �����壺��LogicSystem���캯��RegGet lambda���ʽ
	_post_handlers[path](connection);
	return true;
}




LogicSystem::~LogicSystem()
{
}
