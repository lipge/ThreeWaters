#include "ChatGrpcClient.h"
#include "ConfigMgr.h"
#include "const.h"

ChatConnectionPool::ChatConnectionPool(size_t poolSize, std::string host, std::string port)
	:_poolSize(poolSize), _host(host), _port(port)
{
	for (int i = 0; i < _poolSize; i++) {

		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
		_connections.push(ChatService::NewStub(channel));
	}

}

ChatConnectionPool::~ChatConnectionPool()
{
	std::lock_guard<std::mutex> lock(_mtx);
	while (!_connections.empty()) {
		_connections.pop();
	}
	_stop = true;
	_cv.notify_all();
}

std::unique_ptr<ChatService::Stub> ChatConnectionPool::getConnetcion()
{
	std::unique_lock<std::mutex> lock(_mtx);
	_cv.wait(lock, [this]() {
		if (_stop)return true;
		return !_connections.empty();
		});
	if (_stop)return nullptr;

	auto conn = std::move(_connections.front());
	_connections.pop();
	return conn;
}

void ChatConnectionPool::returnConnetcion(std::unique_ptr<ChatService::Stub> stub)
{
	std::lock_guard<std::mutex> lock(_mtx);
	if (_stop) return;
	_connections.push(std::move(stub));
	_cv.notify_one();
}

AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req)
{
	AddFriendRsp rsp;
	rsp.set_error(ErrorCodes::Success);
	Defer derfer([&req, &rsp] {
		rsp.set_applyuid(req.applyuid());
		rsp.set_touid(req.touid());

		});
	if (_pools.count(server_ip) == 0)return rsp;

	// 拿到对方连接池
	auto& pool = _pools[server_ip];
	// 取到连接
	auto stub = pool->getConnetcion();
	ClientContext context;
	// 直接让对方服务器设置返回值
	Status status = stub->NotifyAddFriend(&context, req, &rsp);

	if (!status.ok()) {
		rsp.set_error(ErrorCodes::RPCFailed);
		pool->returnConnetcion(std::move(stub));
		return rsp;
	}
	pool->returnConnetcion(std::move(stub));
	return rsp;
}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req)
{
	AuthFriendRsp rsp;
	// 这是GrpcClient初始化时构造的连接池，与从redis中查到的server_ip对比
	if (_pools.count(server_ip) == 0) {
		rsp.set_error(ErrorCodes::RPCFailed);
		return rsp;
	}
	// 拿到对方连接池
	auto& pool = _pools[server_ip];
	// 取到连接
	auto stub = pool->getConnetcion();
	ClientContext context;
	Status status = stub->NotifyAuthFriend(&context, req, &rsp);

	Defer der([&pool, &stub]() {
		pool->returnConnetcion(std::move(stub));
		});
	if (!status.ok()) {
		rsp.set_error(ErrorCodes::RPCFailed);
		return rsp;
	}
	return rsp;
}

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req)
{
	TextChatMsgRsp rsp;
	auto& pool = _pools[server_ip];
	auto stub = pool->getConnetcion();
	ClientContext context;
	auto status = stub->NotifyTextChatMsg(&context, req, &rsp);
	if (!status.ok()) {
		pool->returnConnetcion(std::move(stub));
		rsp.set_error(ErrorCodes::RPCFailed);
		return rsp;
	}
	pool->returnConnetcion(std::move(stub));
	return rsp;
}

ChatGrpcClient::ChatGrpcClient()
{
	auto& cfg = ConfigMgr::GetInstance();
	auto server_list = cfg["PeerServer"]["Servers"];

	std::vector<std::string> words;
	std::stringstream ss(server_list);
	std::string word;

	while (std::getline(ss, word, ',')) {
		words.push_back(word);
	}

	for (auto& it : words) {
		_pools[cfg[it]["Name"]] = std::make_unique<ChatConnectionPool>(5, cfg[it]["Host"], cfg[it]["Port"]);
		std::cout << cfg[it]["Name"] << std::endl;
	}

}
