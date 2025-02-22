#pragma once
#include "singleton.h"
#include "MysqlDao.h"
class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	// 将注册用户信息写到Mysql
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePwd(const std::string& email, const std::string& pwd);
	// 登录时检测密码邮箱是否匹配
	bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
	// 有新的好友请求，更新数据库`friend_apply`表
	bool addFriendApply(const int& fromUid, const int& toUid);
	// 同意好友请求，更新数据库`friend`表
	bool authFriendApply(const int& uid, const int& touid);

	// 获取到ChatServer，准备用户登录信息的操作：
	std::shared_ptr<UserInfo> getUser(int uid);
	std::shared_ptr<UserInfo> getUser(std::string name);
	// 获取好友申请列表
	bool getFriendApplicationList(int uid, std::vector<std::shared_ptr<ApplyInfo>>& list);
	// 获取好友列表
	bool getFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list);
private:
	MysqlMgr() {};
	MysqlDao _dao;
};

