#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"


using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;				// 
using message::GetVarifyRsp;				// �ذ�
using message::VarifyService;				// ����


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
	std::queue<std::unique_ptr<VarifyService::Stub>> _connections;		// ���Ӷ���
	std::condition_variable  _cond;										// �̰߳�ȫ����������
	std::mutex _mutex;													// ���������û�����
};

class VerifygRPCClient:public Singleton<VerifygRPCClient>
{
	friend class Singleton<VerifygRPCClient>;
public:
	GetVarifyRsp GetVarifyCode(std::string email); 			// ��ȡ��֤��
	

private:
	VerifygRPCClient();

	std::unique_ptr<RPConPool> _pool;
};

