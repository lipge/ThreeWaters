#include "AsioServicePool.h"



AsioServicePool::AsioServicePool(std::size_t size)
	:_works(size),_iocs(size),_nextIoc(0)
{
	for (std::size_t i = 0; i < size; i++) {
		_works[i] = std::unique_ptr<Work>(new Work(_iocs[i]));

	}

	for (std::size_t i = 0; i < _iocs.size(); i++) {
		_threads.emplace_back([this,i]() {
			_iocs[i].run();
			});

	}


}
boost::asio::io_context& AsioServicePool::GetNowioc()
{
	if (_nextIoc == _iocs.size())
		_nextIoc = 0;
	return _iocs[_nextIoc++];
}

void AsioServicePool::Stop()
{
	for (auto& ioc : _iocs) {
		ioc.stop();
	}
	for (auto& t : _threads) {
		t.join();
	}
}

