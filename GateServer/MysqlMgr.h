#pragma once
#include "singleton.h"
#include "MysqlDao.h"
class MysqlMgr: public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd, const std::string& icon);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePwd(const std::string& email, const std::string& pwd);
	// µ«¬º ±ºÏ≤‚√‹¬Î” œ‰ «∑Ò∆•≈‰
	bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
private:
	MysqlMgr() {};
	MysqlDao _dao;
};

