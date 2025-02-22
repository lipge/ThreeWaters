#pragma once
#include "const.h"


class HttpConnection :public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(boost::asio::io_context& ioc);
	void Start();
	tcp::socket& GetSocket();
private:
	void CheckDeadline();
	void WriteResponse();
	void HandleReq();

	void PreParseGetParam();
	
	tcp::socket _socket;
	beast::flat_buffer _buffer{ 8192 };
	http::request<http::dynamic_body> _request;
	http::response<http::dynamic_body> _response;

	std::string _url;
	std::unordered_map<std::string, std::string> _get_params;

	// 构造定时器
	boost::asio::steady_timer deadline_{
		_socket.get_executor(),std::chrono::seconds(60)
	};
};

