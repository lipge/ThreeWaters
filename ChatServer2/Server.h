#pragma once
#include<boost/asio.hpp>
#include<unordered_map>
#include<string>
#include<mutex>
#include"Session.h"
class Server: public std::enable_shared_from_this<Server>
{
	using tcp = boost::asio::ip::tcp;
public:
	Server(boost::asio::io_context& ioc,u_short port);
	void StartServer();
	void clearSession(std::string session_id);
private:
	boost::asio::ip::tcp::acceptor _acptor;
	std::unordered_map<std::string, std::shared_ptr<Session>> _sessions;
	std::mutex _mtx;
};

