#include "Session.h"
#include "const.h"
#include <boost/uuid.hpp>
#include <iostream>
#include "MsgNode.h"
#include "LogicSystem.h"

Session::Session(boost::asio::io_context& ioc)
	:_socket(ioc), _user_id(0)
{
	boost::uuids::uuid uid = boost::uuids::random_generator()();
	_session_id = boost::uuids::to_string(uid);

	recv_head = new char[HEAD_TOTAL_LEN];
}
Session::~Session()
{
	delete[]recv_head;
	recv_head = nullptr;
}
boost::asio::ip::tcp::socket& Session::GetSocket()
{
	return _socket;
}

static bool dealHead(u_short id = 0, u_short len = 0) {
	std::cout << "Msg id: " << id << std::endl;
	std::cout << "Msg len: " << len << std::endl;

	return true;
}

void Session::StartSession()
{
	auto self = shared_from_this();
	try {
		boost::asio::async_read(_socket, boost::asio::buffer(recv_head, HEAD_TOTAL_LEN),
			[self](boost::system::error_code ec, std::size_t bytes_transferred) {

				if (ec) {
					std::cerr << "Read Head Failed" << std::endl;
					return;
				}

				unsigned short id = 0;
				unsigned short len = 0;
				memcpy(&id, self->recv_head, HEAD_ID_LEN);
				memcpy(&len, self->recv_head + HEAD_ID_LEN, HEAD_DATA_LEN);
				dealHead(id, len);

				self->recv_body = std::make_shared<MsgNode>(id, len);

				boost::asio::async_read(self->_socket, boost::asio::buffer(self->recv_body->_data, len),
					[self](boost::system::error_code ec, std::size_t bytes_transferred) {

						if (ec) {
							std::cerr << "Read Body Failed" << std::endl;
							return;
						}

						LogicSystem::GetInstance().PostMsg(std::make_shared<LogicNode>(self->recv_body, self));
						self->StartSession();
					});



			});
	}
	catch (std::exception ex) {
		std::cerr << ex.what() << std::endl;
	}
}

void Session::Send(std::shared_ptr<MsgNode> node)
{
	std::lock_guard<std::mutex> lock(_mtx);
	_send_que.push(node);

	// 防止重复发送了同一个node
	if (_send_que.size() > 1) return;

	auto& ft = _send_que.front();
	auto self = shared_from_this();
	boost::asio::async_write(_socket, boost::asio::buffer(ft->_data, ft->_len),
		std::bind(&Session::HandleSend, this, shared_from_this(), std::placeholders::_1));
}

void Session::Send(char* data, u_short len, u_short id)
{
	std::lock_guard<std::mutex> lock(_mtx);
	auto node = std::make_shared<MsgNode>(id, len, data);
	_send_que.push(node);

	// 防止重复发送了同一个node
	if (_send_que.size() > 1) return;

	auto& ft = _send_que.front();
	auto self = shared_from_this();
	boost::asio::async_write(_socket, boost::asio::buffer(ft->_data, ft->_len),
		std::bind(&Session::HandleSend, this, shared_from_this(), std::placeholders::_1));
}

void Session::Send(std::string msg, u_short id)
{
	std::lock_guard<std::mutex> lock(_mtx);
	auto node = std::make_shared<MsgNode>(id, msg.length(), msg.c_str());
	_send_que.push(node);

	// 防止重复发送了同一个node
	if (_send_que.size() > 1) return;

	auto& ft = _send_que.front();
	auto self = shared_from_this();
	std::cout << "Send Msg_id: " << ft->_msgid << " len: " << ft->_len << std::endl;
	boost::asio::async_write(_socket, boost::asio::buffer(ft->_data, ft->_len),
		std::bind(&Session::HandleSend, this, shared_from_this(), std::placeholders::_1));
}

void Session::HandleSend(std::shared_ptr<Session> self, boost::system::error_code ec)
{
	if (ec) {
		return;
	}
	// 发送成功
	std::lock_guard<std::mutex> lock(self->_mtx);
	self->_send_que.pop();

	if (!self->_send_que.empty()) {
		auto& ft = _send_que.front();
		boost::asio::async_write(_socket, boost::asio::buffer(ft->_data, ft->_len),
			std::bind(&Session::HandleSend, this, shared_from_this(), std::placeholders::_1));
	}
}

const std::string& Session::getSessionId()
{
	return _session_id;
}

void Session::setUserId(int uid)
{
	_user_id = uid;
}

int Session::getUserId()
{
	return _user_id;
}

LogicNode::LogicNode(std::shared_ptr<MsgNode> node, std::shared_ptr<Session> session)
	:_session(session)
{

	_recvnode = std::make_shared<MsgNode>(node->_msgid, node->_len);
	memcpy(_recvnode->_data, node->_data, node->_len);
}
