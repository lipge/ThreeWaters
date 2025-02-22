#pragma once
#include"Singleton.h"

class AsioServicePool :public Singleton<AsioServicePool>
{
	friend class Singleton<AsioServicePool>;

public:
	using Work = boost::asio::io_context::work;
	using WorkPtr = std::unique_ptr<Work>;
	void Stop();
	boost::asio::io_context& GetNowioc();
private:

	AsioServicePool(std::size_t size = 5);// 线程池数量设置为5

	std::vector<boost::asio::io_context> _iocs;
	std::vector<WorkPtr> _works;
	std::vector<std::thread> _threads;
	std::size_t _nextIoc;
};

