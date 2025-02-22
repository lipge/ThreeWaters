#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "data.h"
#include <jdbc/mysql_driver.h>

#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/parameter_metadata.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <memory>
#include <thread>

class SqlConnection {
public:
	SqlConnection(sql::Connection* con, int64_t lasttime) :_con(con), _last_oper_time(lasttime) {};
	std::unique_ptr<sql::Connection> _con;
	int64_t _last_oper_time;						// ���Ӵ��ʱ��
};


class MysqlPool
{
public:
	MysqlPool(const std::string& url,
		const std::string& user,
		const std::string& pass,
		const std::string& schema,
		int poolsize);

	void checkConnection();								// �������
	std::unique_ptr<SqlConnection> getConn();			// ��ȡ����
	void returnConn(std::unique_ptr<SqlConnection> con);// �黹����
	void Close();
	~MysqlPool();
private:
	std::string _url;
	std::string _user;
	std::string _pass;
	std::string _schema;		// ���ݿ���
	int _polSize;
	std::queue<std::unique_ptr<SqlConnection>> _pool;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::atomic<bool> _b_stop;
	std::thread _check_thread;	// ��������߳�
};

class MysqlDao {
public:
	MysqlDao();
	~MysqlDao();
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePwd(const std::string& email, const std::string& pwd);
	// ����¼�������������Ƿ�ƥ��
	bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
	// �û���Ӻ���
	bool addFriendApply(const int& fromUid, const int& toUid);
	// �û�ͬ����Ӻ���
	bool authFriendApply(const int& uid, const int& touid);
	
	// ��ȡ��ChatServer��׼���û���¼��Ϣ�Ĳ���
	std::shared_ptr<UserInfo> getUser(int uid);
	std::shared_ptr<UserInfo> getUser(std::string name);
	// �����Լ���uid��ȡ���������б�
	bool getFriendApplicationList(int uid, std::vector<std::shared_ptr<ApplyInfo>>& list);
	// �����Լ���uid��ȡ������Ϣ�б�
	bool getFriendList(int uid, std::vector<std::shared_ptr<UserInfo>>& list);
private:
	std::unique_ptr<MysqlPool> _sqlpool;
};