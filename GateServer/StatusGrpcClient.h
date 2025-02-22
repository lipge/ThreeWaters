#pragma once
#include "message.grpc.pb.h"
#include "message.pb.h"
#include "ConfigMgr.h"
#include "const.h"
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::StatusService;

class StatusConPool {
public:
	StatusConPool(size_t poolSzie, std::string host, std::string port) 
		:_pol_size(poolSzie),_host(host),_port(port),_stop(false)
	{
		for (int i = 0; i < _pol_size; i++) {
			std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
			_connections.push(StatusService::NewStub(channel));
		}
	}
	~StatusConPool() {

		std::lock_guard<std::mutex> lock(_mutex);
		Close();
		while (!_connections.empty()) {
			_connections.pop();
		}
	}

	std::unique_ptr<StatusService::Stub> getConn() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [this]() {
			if (_stop) {
				return true;
			}
			return !_connections.empty();
			});
		if (_stop) {
			return nullptr;
		}
		auto con = std::move(_connections.front());
		_connections.pop();
		return con;
	}
	void returnConnection(std::unique_ptr<StatusService::Stub> context) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_stop) {
			return;
		}
		_connections.push(std::move(context));
		_cond.notify_one();
	}
	void Close() {
		_stop = true;
	}
private:
	size_t _pol_size;
	std::string _host;
	std::string _port;
	std::atomic<bool> _stop;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::queue<std::unique_ptr<StatusService::Stub>> _connections;
};

class StatusGrpcClient :public Singleton<StatusGrpcClient>
{
	friend class Singleton<StatusGrpcClient>;
public:
	~StatusGrpcClient(){}

	GetChatServerRsp GetChatServer(int uid);
	LoginRsp Login(int uid, std::string token);

private:
	StatusGrpcClient();
	std::unique_ptr<StatusConPool> _pool;
};