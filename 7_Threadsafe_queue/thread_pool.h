#pragma once

#include <iostream>
#include <future>
#include <vector>
#include <thread>
#include <latch>

#include "safe_queue.h"
#include "safe_queue.cpp"

extern std::mutex cout_m;

class thread_pool
{
public:
	thread_pool();
	thread_pool(const thread_pool& other) = delete;
	thread_pool(const thread_pool&& other) = delete;
	void work(std::stop_token stop);
		
	void submit(std::packaged_task<void()> task);

	~thread_pool();

private:
	const int _cores = std::thread::hardware_concurrency();
	std::latch _wait_cores{ _cores };
	std::vector<std::jthread> _pool;
	safe_queue<std::packaged_task<void()>> _tasks;
	std::stop_source _stoper;
};

