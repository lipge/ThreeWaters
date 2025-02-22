#pragma once
#include<boost/asio.hpp>
#include"MsgNode.h"
#include<mutex>
#include<queue>
class Session:public std::enable_shared_from_this<Session>
{
	using tcp = boost::asio::ip::tcp;
public:
	Session(boost::asio::io_context& ioc);
	~Session();
	tcp::socket& GetSocket();
	const std::string& getSessionId();
	void StartSession();

	void Send(std::shared_ptr<MsgNode> node);
	void Send(char* data, u_short len, u_short id);
	void Send(std::string msg, u_short id);


	// 绑定用户id
	void setUserId(int uid);
	int getUserId();

	// AI::
	//void ReadHead();
	//void ReadBody(unsigned short id, unsigned short len);

private:
	void HandleSend(std::shared_ptr<Session> self,boost::system::error_code ec);

	tcp::socket _socket;
	std::string _session_id;

	char* recv_head;
	std::shared_ptr<MsgNode> recv_body;

	std::queue<std::shared_ptr<MsgNode>> _send_que;
	std::mutex _mtx;

	// 用户uid
	int _user_id;
};

class LogicNode {
public:
	LogicNode(std::shared_ptr<MsgNode> node, std::shared_ptr<Session> session);
	std::shared_ptr<MsgNode> _recvnode;
	std::shared_ptr<Session> _session;

};