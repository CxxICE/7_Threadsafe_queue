#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

extern std::mutex cout_m;

template <typename T>
class safe_queue
{
public:
	safe_queue();

	void push(T obj);
	T pop();
	bool empty();
	std::condition_variable &get_done();

private:
	std::mutex _m;
	std::condition_variable _done;
	std::queue<T> _queue;
	std::atomic_flag _empty;
};

