#include "HttpConnection.h"
#include "LogicSystem.h"
HttpConnection::HttpConnection(boost::asio::io_context& ioc)
	:_socket(ioc)
{

}

void HttpConnection::Start()
{
	
	auto self = shared_from_this();
	http::async_read(_socket, _buffer, _request, [self](boost::beast::error_code ec, std::size_t bytes_transferred) {

		try {
			if (ec) {
				std::cout << "Http read ec is" << ec.what() << std::endl;
				return;
			}
			boost::ignore_unused(bytes_transferred);
			self->HandleReq();
			self->CheckDeadline();
		}
		catch (std::exception& exp) {
			std::cout << "Exception is" << exp.what() << std::endl;
		}

		});
}
tcp::socket& HttpConnection::GetSocket()
{
	return _socket;
}

// 定时器超时 时触发，服务器关闭客户端
void HttpConnection::CheckDeadline()
{
	auto self = shared_from_this();
	deadline_.async_wait([self](beast::error_code ec) {

		if (!ec) {
			self->_socket.close(ec);
		}

		});
}

unsigned char ToHex(unsigned char x) {

	return x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x) {
	unsigned char y;
	if (x >= 'A' && x <= 'Z')y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z')y = x - 'a' + 10;
	else if (x >= '0' && x <= '9')y = x - '0';
	else assert(0);
	return y;
}

std::string UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		//判断是否仅有数字和字母构成
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ') //为空字符
			strTemp += "+";
		else
		{
			//其他字符需要提前加%并且高四位和低四位分别转为16进制
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] & 0x0F);
		}
	}
	return strTemp;
}

std::string UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		//还原+为空
		if (str[i] == '+') strTemp += ' ';
		//遇到%将后面的两个字符从16进制转为char再拼接
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}

void HttpConnection::WriteResponse()
{
	auto self = shared_from_this();
	// 回应长度与请求长度保持一致
	_response.content_length(_response.body().size());
	http::async_write(_socket, _response, [self](beast::error_code ec, std::size_t bytes_transferred) {
		
		// 短连接，关闭服务端的发送
		self->_socket.shutdown(tcp::socket::shutdown_send, ec);
		
		// 更新定时器
		self->deadline_.cancel();
		});
}

void HttpConnection::HandleReq()
{
	// 回应版本与请求版本保持一致
	_response.version(_request.version());
	// 不需要保活，不需要维持长连接
	_response.keep_alive(false);
	// GET请求
	if (_request.method() == http::verb::get) {

		PreParseGetParam();							// 解析url，解析结果放到了类私有成员中

		bool success = LogicSystem::GetInstance()->HandleGet(_url, shared_from_this());				// 处理GET请求

		if (!success) {
			_response.result(http::status::not_found);
			_response.set(http::field::content_type, "text/plain");						// http响应体类型
			beast::ostream(_response.body()) << "Url not found\r\n";					// http响应体内容
			WriteResponse();
			return;
		}

		_response.result(http::status::ok);
		_response.set(http::field::server, "GateServer");								// http服务器名称
		WriteResponse();																// 回应GET请求
		return;
	}

	// POST请求
	if (_request.method() == http::verb::post) {

		bool success = LogicSystem::GetInstance()->HandlePost(_request.target(), shared_from_this());				// 处理POST请求

		if (!success) {
			_response.result(http::status::not_found);
			_response.set(http::field::content_type, "text/plain");						// http响应体类型
			beast::ostream(_response.body()) << "Url not found\r\n";					// http响应体内容
			WriteResponse();
			return;
		}

		_response.result(http::status::ok);
		_response.set(http::field::server, "GateServer");								// http服务器名称
		WriteResponse();																// 回应GET请求
		return;
	}
}


void HttpConnection::PreParseGetParam()
{
	auto uri = _request.target();					// 返回一个string_view,只包含头指针、长度。方便查询

	auto query_pos = uri.find('?');
	if (query_pos == std::string::npos) {			// 没有'?'，只是访问页面
		_url = uri;
		return;
	}

	_url = uri.substr(0, query_pos);				// 问号?前边的部分

	std::string query_string = uri.substr(query_pos + 1);					// 查询字符串.?后边的部分
	std::string key;
	std::string value;
	int pos = -1;
	// "?spm_id_from=333.788.videopod.sections"&vd_source=54414f12ac568080c6f8ee3f809ff41d"
	while ((pos = query_string.find('&')) != std::string::npos) {			// 寻找每个'&'

		auto pair = query_string.substr(0, pos);							// 某个键值对
		size_t eq_pos = pair.find('=');										// 寻找'='
		if (eq_pos != std::string::npos) {									// '='有效
			key = UrlDecode(pair.substr(0, eq_pos));						// key.'='之前
			value = UrlDecode(pair.substr(eq_pos + 1));						// value.'='之后
			_get_params[key] = value;										// 存到unorder_map中
		}
		query_string.erase(0, pos + 1);
	}
	// 最后一个参数对
	if (!query_string.empty()) {
		auto pair = query_string.substr(0, pos);							// 某个键值对
		size_t eq_pos = pair.find('=');										// 寻找'='
		if (eq_pos != std::string::npos) {									// '='有效
			key = UrlDecode(pair.substr(0, eq_pos));						// key.'='之前
			value = UrlDecode(pair.substr(eq_pos + 1));						// value.'='之后
			_get_params[key] = value;										// 存到unorder_map中
		}
	}


}

