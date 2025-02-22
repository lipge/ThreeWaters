#include "VerifygRPCClient.h"
#include "ConfigMgr.h"

// 自己封装的类中 自己定义的GetVarifyCode函数
GetVarifyRsp VerifygRPCClient::GetVarifyCode(std::string email)
{
	ClientContext context;
	GetVarifyRsp reply;
	GetVarifyReq request;

	// !!!
	request.set_email(email);

	auto stub = _pool->getConnection();
	// 在proto序列化中，定义的一个grpc服务，这个服务(函数)也叫GetVarifyCode，
	Status status = stub->GetVarifyCode(&context, request, &reply);
	if (status.ok()) {
		_pool->returnConnection(std::move(stub));
		reply.set_error(ErrorCodes::Success);
		return reply;
	}
	else {
		_pool->returnConnection(std::move(stub));
		reply.set_error(ErrorCodes::RPCFailed);
		return reply;
	}
}

VerifygRPCClient::VerifygRPCClient()
{
	auto& gCfgMgr = ConfigMgr::GetInstance();
	std::string host = gCfgMgr["VarifyServer"]["Host"];
	std::string port = gCfgMgr["VarifyServer"]["Port"];
	_pool.reset(new RPConPool(5, host, port));
}

RPConPool::RPConPool(std::size_t poolsize, std::string host, std::string port)
	:_poolSize(poolsize), _host(host), _port(port), _b_stop(false)
{
	for (size_t i = 0; i < _poolSize; i++) {
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port,
			grpc::InsecureChannelCredentials());
		_connections.push(VarifyService::NewStub(channel));
	}
}

RPConPool::~RPConPool()
{
	std::lock_guard<std::mutex> _lock(_mutex);
	Close();
	while (!_connections.empty()) {
		_connections.pop();
	}
}

void RPConPool::Close()
{
	_b_stop = true;
	_cond.notify_all();
}

std::unique_ptr<VarifyService::Stub> RPConPool::getConnection()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this]() {
		if (_b_stop) {
			return true;
		}
		return !_connections.empty();
		});
	if (_b_stop) {
		return nullptr;
	}
	auto context = std::move(_connections.front());
	_connections.pop();
	return context;


}

void RPConPool::returnConnection(std::unique_ptr<VarifyService::Stub> context)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_connections.push(std::move(context));
	_cond.notify_one();
}
