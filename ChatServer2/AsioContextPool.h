#pragma once
#include"Singleton.h"
#include<vector>
#include<memory>
#include<boost/asio.hpp>

class AsioContextPool:public Singleton<AsioContextPool>
{
	friend class Singleton<AsioContextPool>;
public:
	using Work = boost::asio::io_context::work;
	~AsioContextPool();
	boost::asio::io_context& getIoc();

private:
	AsioContextPool();
	std::vector<boost::asio::io_context> _iocs;
	std::vector<std::thread> _threads;
	std::vector<Work> _works;
	int _nextIoc;

};

