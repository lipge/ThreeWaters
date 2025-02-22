#include "UserMgr.h"
#include"Session.h"
#include"RedisMgr.h"

UserMgr::~UserMgr()
{
	std::lock_guard<std::mutex> lock(_session_mtx);
	_uid_to_session.clear();
}

std::shared_ptr<Session> UserMgr::getSession(int uid)
{
	std::lock_guard<std::mutex> lock(_session_mtx);
	if (_uid_to_session.count(uid) == 0)return nullptr;
	return _uid_to_session[uid];
}

void UserMgr::setSession(int uid, std::shared_ptr<Session> session)
{
	std::lock_guard<std::mutex> lock(_session_mtx);
	_uid_to_session[uid] = session;
}

void UserMgr::rmSession(int uid)
{
	std::lock_guard<std::mutex> lock(_session_mtx);
	_uid_to_session.erase(uid);
}
