#include "StatusGrpcClient.h"

GetChatServerRsp StatusGrpcClient::GetChatServer(int uid)
{
	ClientContext context;
	GetChatServerRsp response;
	GetChatServerReq request;
	request.set_uid(uid);
	auto stub = _pool->getConn();
	Status status = stub->GetChatServer(&context, request, &response);
	Defer defer([&stub, this]() {
		_pool->returnConnection(std::move(stub));
		});
	if (!status.ok()) {
		response.set_error(ErrorCodes::RPCFailed);
		return response;
	}
	return response;

}

StatusGrpcClient::StatusGrpcClient()
{
	auto& cfgMgr = ConfigMgr::GetInstance();
	std::string host = cfgMgr["StatusServer"]["Host"];
	std::string port = cfgMgr["StatusServer"]["Port"];
	_pool.reset(new StatusConPool(5, host, port));
}
