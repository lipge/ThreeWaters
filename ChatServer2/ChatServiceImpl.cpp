#include "ChatServiceImpl.h"
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "UserMgr.h"
#include "const.h"
#include "LogicSystem.h"

ChatServiceImpl::ChatServiceImpl()
{
}

Status ChatServiceImpl::NotifyAddFriend(::grpc::ServerContext* context, const::message::AddFriendReq* request, ::message::AddFriendRsp* response)
{
	// �����û��Ƿ�����
	auto touid = request->touid();
	auto session = UserMgr::GetInstance().getSession(touid);

	if (session == nullptr)return Status::OK;

	Json::Value rtVal;
	rtVal["error"] = ErrorCodes::Success;
	rtVal["applyname"] = request->name();
	rtVal["desc"] = request->desc();
	rtVal["uid"] = request->applyuid();
	rtVal["icon"] = request->icon();
	rtVal["sex"] = request->sex();

	session->Send(rtVal.toStyledString(), ID_NOTIFY_ADD_FRIEND_REQ);

	return Status::OK;
}

Status ChatServiceImpl::NotifyAuthFriend(::grpc::ServerContext* context, const::message::AuthFriendReq* request, ::message::AuthFriendRsp* response)
{
	// �����û��Ƿ�����
	int touid = request->touid();
	auto tosession = UserMgr::GetInstance().getSession(touid);
	// �Է�������
	if (tosession == nullptr)return Status::OK;

	// �ٲ��Լ�����Ϣ�������Զ�
	Json::Value Value, tempObj;		// ֪ͨ���Զ˵���Ϣ��֪ͨ�Զ�����ͬ���ˣ�
	auto Info = std::make_shared<UserInfo>();
	int uid = request->fromuid();
	std::string base_key = USER_BASE_INFO + std::to_string(uid);
	LogicSystem::GetInstance().GetBaseInfo(base_key, uid, Info, tempObj);
	Value["error"] = ErrorCodes::Success;
	Value["nick"] = Info->nick;
	Value["name"] = Info->name;
	Value["icon"] = Info->icon;
	Value["sex"] = Info->sex;
	tosession->Send(Value.toStyledString(), ID_NOTIFY_AUTH_FRIEND_REQ);

	response->set_error(ErrorCodes::Success);
	return Status::OK;
}

Status ChatServiceImpl::NotifyTextChatMsg(::grpc::ServerContext* context, const::message::TextChatMsgReq* request, ::message::TextChatMsgRsp* response)
{
	// �����û��Ƿ�����
	int touid = request->touid();
	auto tosession = UserMgr::GetInstance().getSession(touid);
	// �Է�������
	if (tosession == nullptr)return Status::OK;

	Json::Value rtValue;
	Json::Value array;
	for (auto& msg : request->textmsgs()) {
		Json::Value tempJson;
		tempJson["content"] = msg.msgcontent();
		tempJson["msgid"] = msg.msgid();
		array.append(tempJson);
	}
	rtValue["error"] = ErrorCodes::Success;
	rtValue["uid"] = request->fromuid();
	rtValue["touid"] = request->touid();
	rtValue["text_array"] = array;
	tosession->Send(rtValue.toStyledString(), ID_NOTIFY_TEXT_CHAT_MSG_REQ);
	return Status::OK;
}
