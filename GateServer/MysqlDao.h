#pragma once
#include "const.h"

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
	int64_t _last_oper_time;						// 连接存活时间
};

struct UserInfo {
	std::string name;
	std::string pwd;
	std::string email;
	int uid;
};

class MysqlPool
{
public:
	MysqlPool(const std::string& url,
		const std::string& user,
		const std::string& pass,
		const std::string& schema,
		int poolsize);

	void checkConnection();								// 检查连接
	std::unique_ptr<SqlConnection> getConn();			// 获取连接
	void returnConn(std::unique_ptr<SqlConnection> con);// 归还连接
	void Close();
	~MysqlPool();
private:
	std::string _url;
	std::string _user;
	std::string _pass;
	std::string _schema;		// 数据库名
	int _polSize;
	std::queue<std::unique_ptr<SqlConnection>> _pool;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::atomic<bool> _b_stop;
	std::thread _check_thread;	// 检测连接线程
};

class MysqlDao {
public:
	MysqlDao();
	~MysqlDao();
	int RegUser(const std::string& name, const std::string& email, const std::string& pwd, const std::string& icon);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePwd(const std::string& email, const std::string& pwd);
	// 检测登录的密码与邮箱是否匹配
	bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
private:
	std::unique_ptr<MysqlPool> _sqlpool;
};