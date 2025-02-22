#include "AsioContextPool.h"


AsioContextPool::AsioContextPool()
	:_nextIoc(0),_iocs(std::thread::hardware_concurrency() - 5)
{

	for (auto& it : _iocs) {
		_works.emplace_back(it);
		_threads.emplace_back([&it]() {
			it.run();
			});
	}

}
AsioContextPool::~AsioContextPool()
{
	for (auto& ioc : _iocs) {
		ioc.stop();
	}
	for (auto& t : _threads) {
		t.join();
	}
}
boost::asio::io_context& AsioContextPool::getIoc()
{
	if (_nextIoc == size(_iocs)) {
		_nextIoc = 0;
	}

	return _iocs[_nextIoc++];
}