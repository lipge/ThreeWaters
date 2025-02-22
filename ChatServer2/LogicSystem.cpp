#include "LogicSystem.h"
#include <thread>
#include <json/reader.h>
#include <json/value.h>
#include "StatusGrpcClient.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"
#include "UserMgr.h"
#include "data.h"
#include "ChatGrpcClient.h"

LogicSystem::LogicSystem()
{
	_stop.store(false);
	RegisterFuncCall();
	std::thread t(&LogicSystem::DealMsg, this);
	t.detach();
}

LogicSystem::~LogicSystem()
{
	_stop.store(true);
	_cond.notify_one();
	std::cout << "LogicSystem destruct";
}

void LogicSystem::PostMsg(std::shared_ptr<LogicNode> node)
{
	std::lock_guard<std::mutex> lock(_mtx);
	_msg_que.push(node);
	_cond.notify_one();
}

void LogicSystem::DealMsg()
{
	for (;;) {
		std::unique_lock<std::mutex> lock(_mtx);
		_cond.wait(lock, [this]() {
			return !_msg_que.empty() || _stop;
			});

		// �ط���ֱ�ӻ�ȡһ��������ն���
		if (_stop) {
			while (!_msg_que.empty()) {
				auto msg = _msg_que.front();
				auto id = msg->_recvnode->_msgid;
				if (_call_back.count(id) != 0) {
					_call_back[id](msg->_session, id, std::string(msg->_recvnode->_data, msg->_recvnode->_len));
				}
				_msg_que.pop();
			}
			return;
		}

		// �Ȼ�ȡ��������
		auto msg = _msg_que.front();
		auto id = msg->_recvnode->_msgid;
		auto callback = _call_back.count(id) != 0 ? _call_back[id] : nullptr;
		auto session = msg->_session;
		std::string data(msg->_recvnode->_data, msg->_recvnode->_len);
		std::cout << data << std::endl;
		// ��pop�����ͷ���
		_msg_que.pop();
		lock.unlock();

		// ������ִ�лص�
		if (callback) {
			callback(session, id, data);
		}
	}
}

void LogicSystem::RegisterFuncCall()
{
	using namespace std;
	// ��tcp��recv�����ֽ��������MSG_CHAT_LOGIN ���������Ϣ��
	_call_back[MSG_CHAT_LOGIN] = std::bind(&LogicSystem::LoginHandler, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	// ��tcp��recv�����ֽ��������ID_SEARCH_USER_REQ ���������Ϣ��
	_call_back[ID_SEARCH_USER_REQ] = std::bind(&LogicSystem::searchUserHandler, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_call_back[ID_ADD_FRIEND_REQ] = std::bind(&LogicSystem::addFriendApply, this,
		placeholders::_1, placeholders::_2, placeholders::_3);

	_call_back[ID_AUTH_FRIEND_REQ] = std::bind(&LogicSystem::authFriendApply, this,
		placeholders::_1, placeholders::_2, placeholders::_3);
	// �����շ��ı���Ϣ
	_call_back[ID_TEXT_CHAT_MSG_REQ] = std::bind(&LogicSystem::dealChatTextMsg, this,
		placeholders::_1, placeholders::_2, placeholders::_3);
}

// ����key��Redis�в�Json���л�����ַ�����������Redis��û���ٸ���uid��Mysql�в�info
bool LogicSystem::GetBaseInfo(std::string key, int uid, std::shared_ptr<UserInfo>& info, Json::Value& jsonVal)
{
	Json::Reader reader;
	Json::Value root;
	std::string value = "";
	bool success = RedisMgr::GetInstance().Get(key, value);			// ��redis�ж����л�����ַ���
	if (success) {													// Redis��û�ж�ӦKey
		reader.parse(value, root);// �����л��ַ���������jsonVal��
		jsonVal = root;
		jsonToinfo(root, info);
	}
	else {
		info = MysqlMgr::GetInstance().getUser(uid);
		if (info == nullptr) return false;					// ��ѯ���ݿ�ʧ��

		infoTojson(info, jsonVal);
		RedisMgr::GetInstance().Set(key, jsonVal.toStyledString());// ��Redis��һ��
	}
	return true;
}

void LogicSystem::LoginHandler(std::shared_ptr<Session> session, const USHORT& id, const std::string& msg)
{
	Json::Reader reader;
	Json::Value root;
	Json::Value res;
	reader.parse(msg, root);

	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();
	std::cout << "Usr uid: " << uid << std::endl;
	std::cout << "Usr token: " << token << std::endl;

	Defer defer([this, &res, session]() {
		session->Send(res.toStyledString(), MSG_CHAT_LOGIN_RSP);
		});

	// ��Redis����֤token
	std::string token_key = USERTOKENPREFIX + std::to_string(uid);
	std::string token_value = "";
	bool success = RedisMgr::GetInstance().Get(token_key, token_value);

	if (!success) {
		res["error"] = ErrorCodes::UidInvalid;
		return;
	}
	if (token_value != token) {
		res["error"] = ErrorCodes::TokenInvalid;
		return;
	}

	auto base_key = USER_BASE_INFO + std::to_string(uid);
	auto user_info = std::make_shared<UserInfo>();
	success = GetBaseInfo(base_key, uid, user_info, res);
	if (!success) {
		res["error"] = ErrorCodes::UidInvalid;
		return;
	}


	// ��¼�ɹ���
	res["error"] = ErrorCodes::Success;
	res["uid"] = user_info->uid;
	res["name"] = user_info->name;
	res["nick"] = user_info->nick;
	res["email"] = user_info->email;
	res["icon"] = user_info->icon;
	res["sex"] = user_info->sex;

	// 1.�����ݿ��ȡ�����б�
	std::vector<std::shared_ptr<ApplyInfo>> list;
	success = MysqlMgr::GetInstance().getFriendApplicationList(uid, list);
	if (success) {
		for (auto& iter : list) {
			Json::Value obj;
			obj["uid"] = iter->_uid;
			obj["name"] = iter->_name;
			obj["nick"] = iter->_nick;
			obj["icon"] = iter->_icon;
			obj["sex"] = iter->_sex;
			//obj["status"] = iter->_status;
			res["apply_list"].append(obj);
		}
	}
	// 2.��ȡ�����б�
	std::vector<std::shared_ptr<UserInfo>> friend_list;
	success = MysqlMgr::GetInstance().getFriendList(uid, friend_list);
	if (success) {
		for (auto& iter : friend_list) {
			Json::Value obj;
			obj["uid"] = iter->uid;
			obj["name"] = iter->name;
			obj["nick"] = iter->nick;
			obj["icon"] = iter->icon;
			obj["sex"] = iter->sex;
			obj["email"] = iter->email;
			res["friend_list"].append(obj);
		}
	}
	// 3.������������
	std::string self = ConfigMgr::GetInstance().getValue("SelfServer", "Name"); // ��ȡ��ǰ��������
	std::string cnt_str = RedisMgr::GetInstance().HGet(LOGIN_COUNT, self);		// ��ѯ��������
	RedisMgr::GetInstance().HSet(LOGIN_COUNT, self, std::to_string(std::stoi(cnt_str) + 1));// ����������1����д����Redis
	std::cout << "Current: " << self << "  Connections: " << std::stoi(cnt_str) + 1;
	// 4.session���û�uid
	session->setUserId(uid);
	UserMgr::GetInstance().setSession(uid, session);
	// 5.Ϊ�û����õ�¼ip server������
	std::string ipkey = USERIPPREFIX + std::to_string(uid);
	RedisMgr::GetInstance().Set(ipkey, self);
}

void LogicSystem::searchUserHandler(std::shared_ptr<Session> session, const USHORT&, const std::string& styled_msg)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(styled_msg, root);
	auto uid = root["uid"].asString();

	Json::Value rtvalue;
	Defer defer([this, &rtvalue, session]() {
		session->Send(rtvalue.toStyledString(), MSG_IDS::ID_SEARCH_USER_RSP);
		});
	bool success;
	// uid�Ǵ�����
	if (isPureNum(uid)) {
		success = getUserByUid(uid, rtvalue);
	}
	else {
		success = getUserByName(uid, rtvalue);
	}
	if (success) {
		rtvalue["error"] = ErrorCodes::Success;
	}
	else rtvalue["error"] = ErrorCodes::UidInvalid;
}


void LogicSystem::addFriendApply(std::shared_ptr<Session> session, const USHORT&, const std::string& msg)
{
	Json::Value root;
	Json::Reader reader;
	reader.parse(msg, root);
	auto fromuid = root["uid"].asInt();
	auto applyname = root["applyname"].asString();
	auto desc = root["desc"].asString();
	auto icon = root["icon"].asString();
	auto touid = root["touid"].asInt();

	Json::Value rtValue;
	rtValue["error"] = ErrorCodes::Success;
	// ���Լ��ذ����жϷ��������Ƿ�ɹ�
	Defer defer([this, session, &rtValue, fromuid, touid]() {

		session->Send(rtValue.toStyledString(), ID_ADD_FRIEND_RSP);
		});

	// �������ݿ⣬������������Ϣ�浽���ݿ���һ��
	bool success = MysqlMgr::GetInstance().addFriendApply(fromuid, touid);
	if (!success) {
		rtValue = ErrorCodes::UidInvalid;
		return;
	}
	// ��ѯ�Է�ip
	auto key = USERIPPREFIX + std::to_string(touid);
	std::string serverName = "";
	success = RedisMgr::GetInstance().Get(key, serverName);
	if (!success) {// �Է�û�ж�Ӧ�ķ�����
	//	rtValue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	auto info = std::make_shared<UserInfo>();
	Json::Value tempObj;
	auto base_key = USER_BASE_INFO + std::to_string(fromuid);
	GetBaseInfo(base_key, fromuid, info, tempObj);
	if (ConfigMgr::GetInstance().getValue("SelfServer", "Name") == serverName) {  // ��Է���ͬһ��������

		auto tosession = UserMgr::GetInstance().getSession(touid);
		if (tosession) {
			Json::Value notify;
			notify["error"] = ErrorCodes::Success;
			notify["applyname"] = applyname;
			notify["desc"] = desc;
			notify["uid"] = fromuid;
			notify["icon"] = info->icon;
			notify["sex"] = info->sex;
			tosession->Send(notify.toStyledString(), ID_NOTIFY_ADD_FRIEND_REQ);
			return;
		}
	}

	// �Է�����ͬһ��������
	AddFriendReq add_req;
	add_req.set_applyuid(fromuid);
	add_req.set_touid(touid);
	add_req.set_name(applyname);
	add_req.set_desc(desc);
	add_req.set_icon(info->icon);
	add_req.set_sex(info->sex);

	ChatGrpcClient::GetInstance().NotifyAddFriend(serverName, add_req);
}

void LogicSystem::authFriendApply(std::shared_ptr<Session> session, const USHORT&, const std::string& msg)
{
	Json::Value root;
	Json::Value tempObj;
	Json::Reader reader;
	reader.parse(msg, root);
	// uid�û�ͬ����touid�ĺ�������
	auto uid = root["uid"].asInt();
	auto touid = root["touid"].asInt();
	auto remark = root["remark"].asString();

	std::string to_base_key = USER_BASE_INFO + std::to_string(touid);
	auto toInfo = std::make_shared<UserInfo>();
	auto Info = std::make_shared<UserInfo>();
	Json::Value toValue;	// �ظ���ͬ��˵���Ϣ

	Defer defer([session, &toValue]() {
		session->Send(toValue.toStyledString(), ID_AUTH_FRIEND_RSP);// �ظ���ͬ��ˣ���֤�ˣ�
		});

	// �Ȳ�Զ˵���Ϣ�������Լ�
	bool success = GetBaseInfo(to_base_key, touid, toInfo, tempObj);
	if (!success) {
		toValue["error"] = ErrorCodes::UidInvalid;
	}
	toValue["error"] = ErrorCodes::Success;
	toValue["nick"] = toInfo->nick;
	toValue["name"] = toInfo->name;
	toValue["icon"] = toInfo->icon;
	toValue["sex"] = toInfo->sex;
	toValue["remark"] = remark;

	// �������ݿ⣬������������Ϣ״̬����һ�£�����friend���в�������
	success = MysqlMgr::GetInstance().authFriendApply(uid, touid);
	if (!success) {
		toValue["error"] = ErrorCodes::UidInvalid;
		return;
	}

	/*-------------------------------�����ǶԷ�������Ҫ����֪ͨ----------------------*/
	// ��ѯ�Է�ip
	std::string serverName = "";
	auto key = USERIPPREFIX + std::to_string(touid);
	success = RedisMgr::GetInstance().Get(key, serverName);
	if (!success) {// �Է�û�ж�Ӧ�ķ�����
		return;
	}
	if (ConfigMgr::GetInstance().getValue("SelfServer", "Name") == serverName) {  // ��Է���ͬһ��������
		auto tosession = UserMgr::GetInstance().getSession(touid);
		if (tosession) {
			Json::Value value;
			std::string base_key = USER_BASE_INFO + std::to_string(uid);// ���Լ�����Ϣ�����Զ�
			GetBaseInfo(base_key, uid, Info, tempObj);
			value["error"] = ErrorCodes::Success;
			value["nick"] = Info->nick;
			value["name"] = Info->name;
			value["icon"] = Info->icon;
			value["sex"] = Info->sex;
			tosession->Send(value.toStyledString(), ID_NOTIFY_AUTH_FRIEND_REQ);
			return;
		}
		// �Է�������
		// ...
		return;
	}
	// �Է�����ͬһ��������
	AuthFriendReq auth_req;
	auth_req.set_fromuid(uid);
	auth_req.set_touid(touid);
	ChatGrpcClient::GetInstance().NotifyAuthFriend(serverName, auth_req);
}

void LogicSystem::dealChatTextMsg(std::shared_ptr<Session> session, const USHORT&, const std::string& msg)
{
	Json::Value root;
	Json::Value tempObj;
	Json::Reader reader;
	reader.parse(msg, root);
	// uid�û���touid���ѷ�����Ϣ
	auto uid = root["uid"].asInt();
	auto touid = root["touid"].asInt();
	Json::Value text_arry = root["text_array"];

	Json::Value value;
	value["error"] = ErrorCodes::Success;
	value["uid"] = uid;
	value["touid"] = touid;
	value["text_array"] = text_arry;
	// �ȸ��Լ��ظ�
	Defer defer([session, &value]() {
		session->Send(value.toStyledString(), ID_TEXT_CHAT_MSG_RSP);
		});

	/*-------------------------------�ظ����Զ�--------------------------*/

	std::string serverName = "";
	auto key = USERIPPREFIX + std::to_string(touid);
	bool success = RedisMgr::GetInstance().Get(key, serverName);
	if (!success) {// �Է�û�ж�Ӧ�ķ�����
		value["error"] = ErrorCodes::UidInvalid;
		return;
	}
	if (ConfigMgr::GetInstance().getValue("SelfServer", "Name") == serverName) {  // ��Է���ͬһ��������
		auto tosession = UserMgr::GetInstance().getSession(touid);
		if (tosession) {
			tosession->Send(value.toStyledString(), ID_NOTIFY_TEXT_CHAT_MSG_REQ);
			return;
		}	
		// �Է�������
		// ...
		return;
	}


	// �Է�����ͬһ��������
	TextChatMsgReq message_req;
	
	message_req.set_fromuid(uid);
	message_req.set_touid(touid);
	for (auto& iter : text_arry) {

		message::TextChatData* data = message_req.add_textmsgs();
		data->set_msgid(iter["msgid"].asString());
		data->set_msgcontent(iter["content"].asString());
	}

	ChatGrpcClient::GetInstance().NotifyTextChatMsg(serverName, message_req);
}




// �ж��ַ����Ƿ��Ǵ�����
bool LogicSystem::isPureNum(std::string uid) {
	for (auto& it : uid) {
		if (it < 48 || it>57)return false;
	}
	return true;
}


// �������޸�json��error�ֶ�
bool LogicSystem::getUserByUid(const std::string& uid, Json::Value& rtVal)
{
	std::shared_ptr<UserInfo> tempObj = std::make_shared<UserInfo>();
	try {
		bool success = GetBaseInfo(USER_BASE_INFO + uid, std::stoi(uid), tempObj, rtVal);
		return success;
	}
	catch (std::exception exp) {
		std::cerr << "Exception: " << exp.what() << std::endl;
		return false;
	}
}

// �������޸�json��error�ֶ�
bool LogicSystem::getUserByName(const std::string& name, Json::Value& rtVal)
{
	std::string key = NAME_INFO + name;	// ׼��Redis key
	std::string styled_str;
	bool success = RedisMgr::GetInstance().Get(key, styled_str);// ��ѯredis
	if (success) {
		Json::Reader reader;
		reader.parse(styled_str, rtVal);
	}
	else {
		auto info_ptr = MysqlMgr::GetInstance().getUser(name);	// redis��û�У���mysql�в�
		if (info_ptr == nullptr)return false;					// mysql��ѯʧ�ܷ���false��������޸�error�ֶ�
		infoTojson(info_ptr, rtVal);
		RedisMgr::GetInstance().Set(key, rtVal.toStyledString());
	}
	return true;
}