#pragma once
#include "Singleton.h"
#include "message.grpc.pb.h"
#include "message.pb.h"
#include <queue>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <atomic>
#include <grpcpp/grpcpp.h>
#include "data.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::ChatService;

using message::AddFriendReq;
using message::AddFriendRsp;
using message::AuthFriendReq;
using message::AuthFriendRsp;
using message::TextChatMsgReq;
using message::TextChatMsgRsp;


class ChatConnectionPool
{
public:
	ChatConnectionPool(size_t poolSize, std::string host, std::string port);
	~ChatConnectionPool();
	std::unique_ptr<ChatService::Stub> getConnetcion();
	void returnConnetcion(std::unique_ptr<ChatService::Stub> stub);

private:

	std::atomic<bool> _stop;
	size_t _poolSize;
	std::string _host;
	std::string _port;
	std::mutex _mtx;
	std::condition_variable _cv;
	std::queue<std::unique_ptr<ChatService::Stub>> _connections;
};

class ChatGrpcClient :public Singleton<ChatGrpcClient>
{
	friend class Singleton<ChatGrpcClient>;
public:
	~ChatGrpcClient() {};
	AddFriendRsp NotifyAddFriend(std::string server_ip, const AddFriendReq& req);
	AuthFriendRsp NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req);
	TextChatMsgRsp NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req);
private:
	ChatGrpcClient();// 构造函数显示私有化
	std::unordered_map<std::string, std::unique_ptr<ChatConnectionPool>> _pools;
};

