#pragma once
#include "Singleton.h"
#include<mutex>
#include<condition_variable>
#include<atomic>
#include<queue>
class RedisConPool {

public:
	RedisConPool(size_t polSize, const char* host, int port, const char* pwd);
	~RedisConPool();

	redisContext* getConnection();
	void returnConnection(redisContext* context);
	void Close();
private:
	size_t _polSize;
	const char* _host;
	const char* _pwd;
	int _port;
	std::queue<redisContext*> _connections;
	std::atomic<bool> _b_stop;
	std::condition_variable _cond;
	std::mutex _mutex;
};


class RedisMgr:public Singleton<RedisMgr>
{
	friend class Singleton<RedisMgr>;

public:
	~RedisMgr();
	
	bool Get(const std::string& key, std::string& value);
	bool Set(const std::string& key, const std::string& value);

	bool LPush(const std::string& key, const std::string& value);
	bool LPop(const std::string& key, std::string& value);
	bool RPush(const std::string& key, const std::string& value);
	bool RPop(const std::string& key, std::string& value);
	bool HSet(const std::string& key, const std::string& hkey, const std::string& value);
	bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
	std::string HGet(const std::string& key, const std::string& hkey);
//	bool HDel(const std::string& key, const std::string& field);
	bool Del(const std::string& key);
	bool ExistsKey(const std::string& key);
	void Close();
	
private:
	RedisMgr();

	std::unique_ptr<RedisConPool> _con_pool;

};

