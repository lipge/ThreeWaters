#pragma once
#include"Singleton.h"
#include<unordered_map>
#include<memory>
#include<mutex>
#include"Session.h"

class Session;
class UserMgr: public Singleton<UserMgr>
{
	friend class Singleton<UserMgr>;

public:
	~UserMgr();
	std::shared_ptr<Session> getSession(int uid);
	void setSession(int uid, std::shared_ptr<Session> session);
	void rmSession(int uid);
	
private:
	UserMgr() {};
	std::mutex _session_mtx;
	std::unordered_map<int, std::shared_ptr<Session>> _uid_to_session;


};

