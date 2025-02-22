#include "RedisMgr.h"
#include "ConfigMgr.h"
#include "const.h"

RedisMgr::RedisMgr()
{
	auto& gCfgMgr = ConfigMgr::GetInstance();
	auto host = gCfgMgr["Redis"]["Host"];
	auto port = gCfgMgr["Redis"]["Port"];
	auto pwd = gCfgMgr["Redis"]["Passwd"];
//	_con_pool.reset(new RedisConPool)
	_con_pool = std::make_unique<RedisConPool>(5, host.c_str(),atoi(port.c_str()), pwd.c_str());
}
RedisMgr::~RedisMgr()
{
	Close();
}





// GET命令
bool RedisMgr::Get(const std::string& key, std::string& value)
{

	auto connection = _con_pool->getConnection();
	{
		redisReply* reply;
		std::string cursor = "0"; // 初始游标

		do {
			// 执行 SCAN 命令
			reply = (redisReply*)redisCommand(connection, "SCAN %s", cursor.c_str());
			if (reply == nullptr) {
				std::cerr << "Error executing SCAN command" << std::endl;
				return false;
			}

			// cursor 是 reply 的第一个元素
			cursor = reply->element[0]->str;

			// reply 的第二个元素是键的列表
			for (size_t i = 0; i < reply->element[1]->elements; ++i) {
				std::string key = reply->element[1]->element[i]->str;

				// 获取每个键的值
				redisReply* valueReply = (redisReply*)redisCommand(connection, "GET %s", key.c_str());
				if (valueReply != nullptr) {
					std::cout << "Key: " << key << ", Value: " << (valueReply->type == REDIS_REPLY_NIL ? "nil" : valueReply->str) << std::endl;
					freeReplyObject(valueReply);
				}
			}

			freeReplyObject(reply);
		} while (cursor != "0"); // 当游标为 0 时，表示遍历完成
	}


	if (connection == nullptr) {
		return false;
		_con_pool->returnConnection(connection);
	}
	auto reply = (redisReply*)redisCommand(connection, "GET %s", key.c_str());

	// 指针为空或者返回类型不是字符串，说明命令请求失败
	if (reply == nullptr || reply->type != REDIS_REPLY_STRING) {			// GET命令请求成功会返回字符串
		std::cerr << "Get Failed! [ GET " << key << " ]" << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}
	value = reply->str;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	std::cout << "Get Success! [ GET " << key << " ]" << std::endl;
	return true;
}

// SET命令
bool RedisMgr::Set(const std::string& key, const std::string& value)
{
	auto connection = _con_pool->getConnection();
	auto reply = (redisReply*)redisCommand(connection, "SET %s %s", key.c_str(), value.c_str());

	// 空指针
	if (reply == nullptr || reply->type != REDIS_REPLY_STATUS) {
		std::cerr << "Set Failed! [ SET " << key << "  " << value << " ]" << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}
	// 返回状态不是OK
	bool ok = (strcmp(reply->str, "OK") == 0 || strcmp(reply->str, "ok") == 0);
	if (!(reply->type == REDIS_REPLY_STATUS && ok)) {
		std::cerr << "Set Failed! [ SET " << key << "  " << value << " ]" << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	std::cout << "Set Success! [ SET " << key << "  " << value << " ]" << std::endl;
	return true;
}


bool RedisMgr::LPush(const std::string& key, const std::string& value)
{
	auto connection = _con_pool->getConnection();
	auto reply = (redisReply*)redisCommand(connection, "LPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == reply)
	{
		std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}

	std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}

bool RedisMgr::LPop(const std::string& key, std::string& value) {
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connection, "LPOP %s ", key.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ LPOP " << key << " ] failure ! " << std::endl;
		_con_pool->returnConnection(connection);
		return false;
	}

	if (reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ LPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}

	value = reply->str;
	std::cout << "Execut command [ LPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}

bool RedisMgr::RPush(const std::string& key, const std::string& value) {
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connection, "RPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == reply)
	{
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}

	std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}
bool RedisMgr::RPop(const std::string& key, std::string& value) {
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connection, "RPOP %s ", key.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
		_con_pool->returnConnection(connection);
		return false;
	}

	if (reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}
	value = reply->str;
	std::cout << "Execut command [ RPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}

bool RedisMgr::HSet(const std::string& key, const std::string& hkey, const std::string& value) {
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connection, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		_con_pool->returnConnection(connection);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}

	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}

bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return false;
	}
	const char* argv[4];
	size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;
	argv[1] = key;
	argvlen[1] = strlen(key);
	argv[2] = hkey;
	argvlen[2] = strlen(hkey);
	argv[3] = hvalue;
	argvlen[3] = hvaluelen;

	auto reply = (redisReply*)redisCommandArgv(connection, 4, argv, argvlen);
	if (reply == nullptr) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		_con_pool->returnConnection(connection);
		freeReplyObject(reply);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] success ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}

std::string RedisMgr::HGet(const std::string& key, const std::string& hkey)
{
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return "";
	}
	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;
	argv[1] = key.c_str();
	argvlen[1] = key.length();
	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();

	auto reply = (redisReply*)redisCommandArgv(connection, 3, argv, argvlen);
	if (reply == nullptr) {
		std::cout << "Execut command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
		_con_pool->returnConnection(connection);
		return "";
	}

	if (reply->type == REDIS_REPLY_NIL) {
		freeReplyObject(reply);
		std::cout << "Execut command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
		_con_pool->returnConnection(connection);
		return "";
	}

	std::string value = reply->str;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	std::cout << "Execut command [ HGet " << key << " " << hkey << " ] success ! " << std::endl;
	return value;
}

//bool RedisMgr::HDel(const std::string& key, const std::string& field)
//{
//	//auto connect = _con_pool->getConnection();
//	if (connect == nullptr) {
//		return false;
//	}
//
//	Defer defer([&connect, this]() {
//		_con_pool->returnConnection(connect);
//		});
//
//	redisReply* reply = (redisReply*)redisCommand(connect, "HDEL %s %s", key.c_str(), field.c_str());
//	if (reply == nullptr) {
//		std::cerr << "HDEL command failed" << std::endl;
//		return false;
//	}
//
//	bool success = false;
//	if (reply->type == REDIS_REPLY_INTEGER) {
//		success = reply->integer > 0;
//	}
//
//	freeReplyObject(reply);
//	return success;
//}
// 删除
bool RedisMgr::Del(const std::string& key)
{
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connection, "DEL %s", key.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ Del " << key << " ] failure ! " << std::endl;
		_con_pool->returnConnection(connection);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ Del " << key << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		_con_pool->returnConnection(connection);
		return false;
	}

	std::cout << "Execut command [ Del " << key << " ] success ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}
// 判断key是否存在
bool RedisMgr::ExistsKey(const std::string& key)
{
	auto connection = _con_pool->getConnection();
	if (connection == nullptr) {
		return false;
	}

	auto reply = (redisReply*)redisCommand(connection, "exists %s", key.c_str());
	if (reply == nullptr) {
		std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
		_con_pool->returnConnection(connection);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer == 0) {
		std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
		_con_pool->returnConnection(connection);
		freeReplyObject(reply);
		return false;
	}
	std::cout << " Found [ Key " << key << " ] exists ! " << std::endl;
	freeReplyObject(reply);
	_con_pool->returnConnection(connection);
	return true;
}
void RedisMgr::Close()
{
	_con_pool->Close();
}



// 连接池
RedisConPool::RedisConPool(size_t polSize, const char* host, int port, const char* pwd)
	:_polSize(polSize), _host(host), _pwd(pwd), _port(port)
{
	for (size_t i = 0; i < _polSize; i++) {
		// 连接
		auto* context = redisConnect(host, port);
		if (context == nullptr || context->err != 0) {
			if (context != nullptr) {
				redisFree(context);
			}
			continue;
		}

		// 认证
		auto reply = (redisReply*)redisCommand(context, "AUTH %s", pwd);
		if (reply->type == REDIS_REPLY_ERROR) {
			std::cerr << "Redis认证失败！" << std::endl;
			freeReplyObject(reply);
			redisFree(context);
			continue;
		}

		// 连接且认证成功
		freeReplyObject(reply);
		std::cout << "Redis认证成功！" << std::endl;
		_connections.push(context);
	}
}

RedisConPool::~RedisConPool()
{
	//std::lock_guard<std::mutex> lock(_mutex);
	//while (!_connections.empty()) {
	//	_connections.pop();
	//}
}

redisContext* RedisConPool::getConnection()
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this] {
		if (_b_stop) {
			return true;
		}
		return !_connections.empty();
		});
	if (_b_stop) {
		return nullptr;
	}
	auto* context = _connections.front();
	_connections.pop();
	return context;
}

void RedisConPool::returnConnection(redisContext* context)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if (_b_stop) {
		return;
	}
	_connections.push(context);
	_cond.notify_one();
}

void RedisConPool::Close()
{
	_b_stop = true;
	_cond.notify_all();
}
