#include "Server.h"
#include "Session.h"
#include "AsioContextPool.h"
#include "UserMgr.h"
Server::Server(boost::asio::io_context& ioc, u_short port)
	:_acptor(ioc,{tcp::v4(),port})
{
}

void Server::StartServer()
{
	auto self = shared_from_this();
	// 1.获取ioc
	auto& ioc = AsioContextPool::GetInstance().getIoc();
	// 2.初始化客户端socket
	tcp::socket sock(ioc);
	auto session = std::make_shared<Session>(ioc);
	_acptor.async_accept(session->GetSocket(), [self, session](boost::system::error_code ec) {
		if (ec) {
			self->StartServer();
			return;
		}
		self->_sessions[session->getSessionId()] = session;
		session->StartSession();
		self->StartServer();
		});
}

void Server::clearSession(std::string session_id)
{
	if (_sessions.count(session_id) != 0) {
		UserMgr::GetInstance().rmSession(_sessions[session_id]->getUserId());
	}

	std::lock_guard<std::mutex> lock(_mtx);
	_sessions.erase(session_id);
}
