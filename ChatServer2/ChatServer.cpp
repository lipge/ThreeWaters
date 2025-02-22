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

		// ����Redis�б���������������
		auto self = cMgr["SelfServer"]["Name"];
		RedisMgr::GetInstance().HSet(LOGIN_COUNT, self, "0");

		ChatServiceImpl gservice;
		grpc::ServerBuilder builder;
		// �����˿�
		builder.AddListeningPort(gaddress, grpc::InsecureServerCredentials());
		// ��ӷ���
		builder.RegisterService(&gservice);
		// ����rpc����
		std::unique_ptr<grpc::Server> gserver(builder.BuildAndStart());
		std::thread gserver_thread([&gserver]() {
			gserver->Wait();
			});


		signals.async_wait([&ioc, &gserver](boost::system::error_code ec, int) {
			std::cout << "Server Quit" << std::endl;
			ioc.stop();
			gserver->Shutdown();// �ر�grpc����
			});
		std::cout << "[ChatServer] Listening on " << port << std::endl;
		std::make_shared<Server>(ioc, port)->StartServer();
		ioc.run();

		// ����redis
		RedisMgr::GetInstance().HDel(LOGIN_COUNT, self);
		RedisMgr::GetInstance().Close();
		gserver_thread.join();
	}
	catch (std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
}