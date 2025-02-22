#include<iostream>
#include"Server.h"
#include"ConfigMgr.h"
#include"RedisMgr.h"
#include"ChatServiceImpl.h"
int main() {

	auto& cMgr = ConfigMgr::GetInstance();

	std::string gate_port = cMgr["SelfServer"]["Port"];
	std::string gaddress = cMgr["SelfServer"]["Host"] + ":" + cMgr["SelfServer"]["RPCPort"];
	u_short port = static_cast<u_short>(atoi(gate_port.c_str()));


	boost::asio::io_context ioc;
	boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);

	try {

		// 重置Redis中本服务器连接数量
		auto self = cMgr["SelfServer"]["Name"];
		RedisMgr::GetInstance().HSet(LOGIN_COUNT, self, "0");

		ChatServiceImpl gservice;
		grpc::ServerBuilder builder;
		// 监听端口
		builder.AddListeningPort(gaddress, grpc::InsecureServerCredentials());
		// 添加服务
		builder.RegisterService(&gservice);
		// 启动rpc服务
		std::unique_ptr<grpc::Server> gserver(builder.BuildAndStart());
		std::thread gserver_thread([&gserver]() {
			gserver->Wait();
			});


		signals.async_wait([&ioc, &gserver](boost::system::error_code ec, int) {
			std::cout << "Server Quit" << std::endl;
			ioc.stop();
			gserver->Shutdown();// 关闭grpc服务
			});
		std::cout << "[ChatServer] Listening on " << port << std::endl;
		std::make_shared<Server>(ioc, port)->StartServer();
		ioc.run();

		// 回收redis
		RedisMgr::GetInstance().HDel(LOGIN_COUNT, self);
		RedisMgr::GetInstance().Close();
		gserver_thread.join();
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
}