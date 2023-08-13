#include "thread_pool.h"

thread_pool::thread_pool()
{
	std::stop_token stop = _stoper.get_token();
	for (int i = 0; i < _cores; ++i)
	{
		_pool.push_back(std::jthread(&thread_pool::work, this, stop));
	}
}

void thread_pool::thread_pool::work(std::stop_token stop)
{
	cout_m.lock();
	std::cout << "Создан поток, id =" << std::this_thread::get_id() << std::endl;
	cout_m.unlock();
	_wait_cores.arrive_and_wait();//ожидание создания требуемого кол-ва потоков
	while (true)
	{
		_tasks.pop()();
		std::this_thread::yield();
		if (stop.stop_requested() && _tasks.empty())
		{
			break;
		}
	};
}

void thread_pool::submit(std::packaged_task<void()> task)
{
	_tasks.push(std::move(task));
}

thread_pool::~thread_pool()
{
	if (_stoper.stop_possible())
	{
		_stoper.request_stop();
	}
	
	for (auto &thread : _pool)
	{
		if (thread.joinable())
		{
			thread.join();
		}		
	}
}


