#pragma once
#include <queue>
#include "MsgNode.h"
#include "Singleton.h"
#include <mutex>
#include <condition_variable>
#include <functional>
#include <map>
#include "Session.h"
#include "data.h"
using FuncCall = std::function<void(std::shared_ptr<Session>, const USHORT&, const std::string&)>;

class LogicSystem:public Singleton<LogicSystem> 
{
	friend class Singleton<LogicSystem>;

public:

	~LogicSystem();
	// 这是外部接口，不需要单独的线程
	void PostMsg(std::shared_ptr<LogicNode> node);
	bool GetBaseInfo(std::string key, int uid, std::shared_ptr<UserInfo>& info, Json::Value& styledJson);

private:
	// 将DealMsg放在单独的线程
	void DealMsg();
	void RegisterFuncCall();
	LogicSystem();
	
	// 处理登录请求
	void LoginHandler(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// 处理用户搜索添加好友逻辑，接收tcp字节流，解析字节流中uid字段。返回完整的搜索信息并序列化
	void searchUserHandler(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// 处理添加好友申请
	void addFriendApply(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// 处理同意好友申请
	void authFriendApply(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// 处理收发文本消息
	void dealChatTextMsg(std::shared_ptr<Session>, const USHORT&, const std::string&);

	// 根据uid查找用户信息
	bool getUserByUid(const std::string& uid, Json::Value&);
	// 根据用户名查找信息
	bool getUserByName(const std::string& name, Json::Value&);
	// 字符串是否是纯数字
	bool isPureNum(std::string uid);

	std::queue<std::shared_ptr<LogicNode>> _msg_que;
	std::mutex _mtx;
	std::condition_variable _cond;
	std::map<unsigned short, FuncCall> _call_back;
	std::atomic<bool> _stop;
};

