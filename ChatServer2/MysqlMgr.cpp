#include "MysqlMgr.h"

MysqlMgr::~MysqlMgr()
{
}

int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
	return _dao.RegUser(name, email, pwd);
}

bool MysqlMgr::CheckEmail(const std::string& name, const std::string& email)
{
	return _dao.CheckEmail(name, email);
}

bool MysqlMgr::UpdatePwd(const std::string& email, const std::string& pwd)
{
	return _dao.UpdatePwd(email, pwd);
}

bool MysqlMgr::CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo)
{
	return _dao.CheckPwd(email, pwd, userInfo);
}

bool MysqlMgr::addFriendApply(const int& uid, const int& touid)
{
	return _dao.addFriendApply(uid, touid);
}

bool MysqlMgr::authFriendApply(const int& uid, const int& touid)
{
	return _dao.authFriendApply(uid, touid);
}

std::shared_ptr<UserInfo> MysqlMgr::getUser(int uid)
{
	return _dao.getUser(uid);
}

std::shared_ptr<UserInfo> MysqlMgr::getUser(std::string name)
{
	return _dao.getUser(name);
}

bool MysqlMgr::getFriendApplicationList(int uid, std::vector<std::shared_ptr<ApplyInfo>>& list)
{
	return _dao.getFriendApplicationList(uid, list);
}

bool MysqlMgr::getFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list)
{
	return _dao.getFriendList(uid, list);
}
