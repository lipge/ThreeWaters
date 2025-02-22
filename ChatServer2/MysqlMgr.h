#pragma once
#include "singleton.h"
#include "MysqlDao.h"
class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	// ��ע���û���Ϣд��Mysql
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePwd(const std::string& email, const std::string& pwd);
	// ��¼ʱ������������Ƿ�ƥ��
	bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
	// ���µĺ������󣬸������ݿ�`friend_apply`��
	bool addFriendApply(const int& fromUid, const int& toUid);
	// ͬ��������󣬸������ݿ�`friend`��
	bool authFriendApply(const int& uid, const int& touid);

	// ��ȡ��ChatServer��׼���û���¼��Ϣ�Ĳ�����
	std::shared_ptr<UserInfo> getUser(int uid);
	std::shared_ptr<UserInfo> getUser(std::string name);
	// ��ȡ���������б�
	bool getFriendApplicationList(int uid, std::vector<std::shared_ptr<ApplyInfo>>& list);
	// ��ȡ�����б�
	bool getFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list);
private:
	MysqlMgr() {};
	MysqlDao _dao;
};

