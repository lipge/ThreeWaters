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
{    // ����token
	boost::uuids::uuid uid = boost::uuids::random_generator()();
	std::string uid_str = boost::uuids::to_string(uid);
	// ��ȡ�������ٵķ����
	const auto& minServer = getMiniServer();
	std::cout << "[State Server]" << std::endl;
	std::cout << "Minserver: " << minServer._host << ":" << minServer._port << std::endl;
	// ����response�ֶ�
	response->set_host(minServer._host);
	response->set_port(minServer._port);
	response->set_error(ErrorCodes::Success);
	response->set_token(uid_str);

	// �״�����utoken��Redis�д�һ��
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
		//��������Ĭ������Ϊ���
		minServer._con_cnt = INT_MAX;
	}
	else { 
		minServer._con_cnt = std::stoi(count_str);
	}
	// ����unordered_map
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