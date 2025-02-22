#include "StatusServiceImpl.h"
#include "const.h"
#include "RedisMgr.h"
#include "boost/uuid.hpp"
#include "ConfigMgr.h"
StatusServiceImpl::StatusServiceImpl()
{
	auto& cfg = ConfigMgr::GetInstance();
	ChatServer server;
	server._host = cfg["ChatServer1"]["Host"];
	server._port = cfg["ChatServer1"]["Port"];
	server._name = cfg["ChatServer1"]["Name"];
	_servers[server._name] = server;

	server._host = cfg["ChatServer2"]["Host"];
	server._port = cfg["ChatServer2"]["Port"];
	server._name = cfg["ChatServer2"]["Name"];
	_servers[server._name] = server;
}
Status StatusServiceImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* response)
{    // 生成token
	boost::uuids::uuid uid = boost::uuids::random_generator()();
	std::string uid_str = boost::uuids::to_string(uid);
	// 获取连接最少的服务端
	const auto& minServer = getMiniServer();
	std::cout << "[State Server]" << std::endl;
	std::cout << "Minserver: " << minServer._host << ":" << minServer._port << std::endl;
	// 设置response字段
	response->set_host(minServer._host);
	response->set_port(minServer._port);
	response->set_error(ErrorCodes::Success);
	response->set_token(uid_str);

	// 首次设置utoken，Redis中存一份
	insertToken(request->uid(), response->token());

	return Status::OK;
}



void StatusServiceImpl::insertToken(int uid, std::string token)
{
	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	RedisMgr::GetInstance()->Set(token_key, token);
}

ChatServer StatusServiceImpl::getMiniServer()
{
	std::lock_guard<std::mutex> guard(_server_mtx);
	auto minServer = _servers.begin()->second;
	auto count_str = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, minServer._name);
	if (count_str.empty()) {
		//不存在则默认设置为最大
		minServer._con_cnt = INT_MAX;
	}
	else { 
		minServer._con_cnt = std::stoi(count_str);
	}
	// 遍历unordered_map
	for (auto& server : _servers) {

		if (server.second._name == minServer._name) {
			continue;
		}

		auto count_str = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server.second._name);
		if (count_str.empty()) {
			server.second._con_cnt = INT_MAX;
		}
		else {
			server.second._con_cnt = std::stoi(count_str);
		}

		if (server.second._con_cnt < minServer._con_cnt) {
			minServer = server.second;
		}
	}

	return minServer;
}