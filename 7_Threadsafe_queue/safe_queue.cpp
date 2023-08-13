#include "safe_queue.h"

template <typename T>
safe_queue<T>::safe_queue()
{
	_empty.test_and_set();
}

template <typename T>
void safe_queue<T>::push(T obj)
{
	{
		std::scoped_lock sl(_m);
		_queue.push(std::move(obj));
		_empty.clear();
	}
	_done.notify_all();
}

template <typename T>
T safe_queue<T>::pop()
{
	T tmp;
	std::unique_lock ul(_m);
	if (_done.wait_for(ul, 1s, [&]() {return !_empty.test(); }))
	{
		tmp = std::move(_queue.front());
		_queue.pop();
		if (_queue.empty())
		{
			_empty.test_and_set();
		}		
	}
	else//холостой ход потока добавлен для возможности проверки во внешней функции был ли stop_requested и последующей остановки всех потоков при уничтожении thread_pool
	{
		if constexpr (std::is_same<T, std::packaged_task<void()>>::value)
		{
			cout_m.lock();
			std::cout << "Холостой ход\tid_потока =\t" << std::this_thread::get_id() << std::endl;
			cout_m.unlock();
			T task([]() {return; });
			tmp = std::move(task);
		}		
	}	
	return tmp;
}

template <typename T>
bool safe_queue<T>::empty()
{
	return _empty.test();
}

template <typename T>
std::condition_variable &safe_queue<T>::get_done()
{
	return _done;
}
