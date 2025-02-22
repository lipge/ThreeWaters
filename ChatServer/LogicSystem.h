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
	// �����ⲿ�ӿڣ�����Ҫ�������߳�
	void PostMsg(std::shared_ptr<LogicNode> node);
	bool GetBaseInfo(std::string key, int uid, std::shared_ptr<UserInfo>& info, Json::Value& styledJson);

private:
	// ��DealMsg���ڵ������߳�
	void DealMsg();
	void RegisterFuncCall();
	LogicSystem();
	
	// �����¼����
	void LoginHandler(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// �����û�������Ӻ����߼�������tcp�ֽ����������ֽ�����uid�ֶΡ�����������������Ϣ�����л�
	void searchUserHandler(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// ������Ӻ�������
	void addFriendApply(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// ����ͬ���������
	void authFriendApply(std::shared_ptr<Session>, const USHORT&, const std::string&);
	// �����շ��ı���Ϣ
	void dealChatTextMsg(std::shared_ptr<Session>, const USHORT&, const std::string&);

	// ����uid�����û���Ϣ
	bool getUserByUid(const std::string& uid, Json::Value&);
	// �����û���������Ϣ
	bool getUserByName(const std::string& name, Json::Value&);
	// �ַ����Ƿ��Ǵ�����
	bool isPureNum(std::string uid);

	std::queue<std::shared_ptr<LogicNode>> _msg_que;
	std::mutex _mtx;
	std::condition_variable _cond;
	std::map<unsigned short, FuncCall> _call_back;
	std::atomic<bool> _stop;
};

