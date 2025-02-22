#include <iostream>
#include "const.h"
#include "ConfigMgr.h"
#include "StatusServiceImpl.h"
#include "RedisMgr.h"
void RunServer() {
    auto& cfg = ConfigMgr::GetInstance();

    std::string server_add(cfg["StatusServer"]["Host"] + ":" + cfg["StatusServer"]["Port"]);
    // 1.注册一个服务
    StatusServiceImpl service;
    grpc::ServerBuilder builder;                // 应该类似listensocket
    // 2.监听端口
    builder.AddListeningPort(server_add, grpc::InsecureServerCredentials());
    // 3.添加服务
    builder.RegisterService(&service);
    // 4.构建并启动grpc
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());

    std::cout << "[State Server] Listening on " << server_add << std::endl;

    boost::asio::io_context ioc;
    boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&server](const boost::system::error_code& ec, int signal) {
        if (!ec) {
            std::cout << "Bye" << std::endl;
            server->Shutdown();
        }
        });
    std::thread([&ioc]() {
        ioc.run();
        }).detach();

    server->Wait();
}

int main()
{
    try {
        RunServer();
        RedisMgr::GetInstance()->Close();
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        RedisMgr::GetInstance()->Close();
        return EXIT_FAILURE;
    }

    return 0;
}


