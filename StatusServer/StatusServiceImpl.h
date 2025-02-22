#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include <mutex>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginReq;
using message::LoginRsp;
using message::StatusService;

struct ChatServer {
public:
	ChatServer():_host(""),_port(""),_name(""),_con_cnt(0){}
	ChatServer(const ChatServer& cs):_host(cs._host),_port(cs._port),_name(cs._name),_con_cnt(cs._con_cnt){}
	ChatServer& operator=(const ChatServer& cs) {
		if (&cs == this) {
			return *this;
		}

		_host = cs._host;
		_port = cs._port;
		_name = cs._name;
		_con_cnt = cs._con_cnt;
		return *this;
	}
	std::string _host;
	std::string _port;
	std::string _name;
	int _con_cnt;
};

class StatusServiceImpl final:public StatusService::Service
{
public:
	StatusServiceImpl();
	Status GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* response) override;
	
private:
	void insertToken(int uid, std::string token);
	ChatServer getMiniServer();
	std::unordered_map<std::string, ChatServer> _servers;
	std::mutex _server_mtx;

};

