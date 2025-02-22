#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"


using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;				// 
using message::GetVarifyRsp;				// 回包
using message::VarifyService;				// 服务


class RPConPool {
public:
	RPConPool(std::size_t poolsize, std::string host, std::string port);
	~RPConPool();
	
	void Close();
	std::unique_ptr<VarifyService::Stub> getConnection();
	void returnConnection(std::unique_ptr<VarifyService::Stub> context);
private:
	std::atomic<bool> _b_stop;
	std::size_t _poolSize;
	std::string _port;
	std::string _host;
	std::queue<std::unique_ptr<VarifyService::Stub>> _connections;		// 连接队列
	std::condition_variable  _cond;										// 线程安全用条件变量
	std::mutex _mutex;													// 操作队列用互斥锁
};

class VerifygRPCClient:public Singleton<VerifygRPCClient>
{
	friend class Singleton<VerifygRPCClient>;
public:
	GetVarifyRsp GetVarifyCode(std::string email); 			// 获取验证码
	

private:
	VerifygRPCClient();

	std::unique_ptr<RPConPool> _pool;
};

