#include "CServer.h"
#include "HttpConnection.h"
#include "AsioServicePool.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port)
	:_ioc(ioc),_acceptor(ioc,tcp::endpoint(tcp::v4(),port))
{

}

void CServer::Start()
{
	auto self = shared_from_this();
	auto& ioc = AsioServicePool::GetInstance()->GetNowioc();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(ioc);
	_acceptor.async_accept(new_con->GetSocket(), [self, new_con](boost::beast::error_code ec) {

		try {
			if (ec) {
				self->Start();
				return;
			}
			// 创建新连接，并创建HttpConnect类管理这个连接
			new_con->Start();
			// 继续监听
			self->Start();
		}
		catch (std::exception& exp) {
			std::cout << "Cserver start Exp:" << exp.what() << std::endl;
		}
		});

}
