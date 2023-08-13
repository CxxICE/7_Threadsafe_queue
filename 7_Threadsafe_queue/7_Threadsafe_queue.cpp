#include <iostream>
#include <mutex>
#include <chrono>
#include <future>

#include "thread_pool.h"

using namespace std::chrono_literals;

std::mutex cout_m;

void green_func()
{
	std::this_thread::sleep_for(100ms);
	std::lock_guard lg(cout_m);
	std::cout << "\x1B[32m" << __func__ << "\x1B[0m" << "\tid_потока =\t" << std::this_thread::get_id() << std::endl;
}

void red_func()
{
	std::this_thread::sleep_for(100ms);
	std::lock_guard lg(cout_m);
	std::cout << "\x1B[31m" << __func__ << "\x1B[0m" << "\tid_потока =\t" << std::this_thread::get_id() << std::endl;
}

void blue_func()
{
	std::this_thread::sleep_for(100ms);
	std::lock_guard lg(cout_m);
	std::cout << "\x1B[34m" << __func__ << "\x1B[0m" << "\tid_потока =\t" << std::this_thread::get_id() << std::endl;
}

void magenta_func()
{
	std::this_thread::sleep_for(100ms);
	std::lock_guard lg(cout_m);
	std::cout << "\x1B[35m" << __func__ << "\x1B[0m" << "\tid_потока =\t" << std::this_thread::get_id() << std::endl;
}


int main()
{
	setlocale(LC_ALL, "RU");
	{
		thread_pool tp;
		for (int i = 0; i < 5; ++i)
		{
			std::this_thread::sleep_for(1s);
			cout_m.lock();			
			
			std::packaged_task<void()> task1(blue_func);
			std::packaged_task<void()> task2(red_func);
			std::jthread t1(&thread_pool::submit, &tp, std::move(task1));
			std::jthread t2(&thread_pool::submit, &tp, std::move(task2));
				
			std::cout << std::endl;
			cout_m.unlock();			
		}
	}

	cout_m.lock();
	std::cout << std::endl;
	cout_m.unlock();

	{
		thread_pool tp;
		for (int i = 0; i < 5; ++i)
		{
			std::this_thread::sleep_for(1s);
			cout_m.lock();
			
			std::packaged_task<void()> task1(blue_func);
			std::packaged_task<void()> task2(blue_func);
			std::packaged_task<void()> task3(magenta_func);
			std::packaged_task<void()> task4(magenta_func);
			std::packaged_task<void()> task5(red_func);
			std::packaged_task<void()> task6(red_func);
			std::packaged_task<void()> task7(green_func);
			std::packaged_task<void()> task8(green_func);
			std::jthread t1(&thread_pool::submit, &tp, std::move(task1));
			std::jthread t2(&thread_pool::submit, &tp, std::move(task2));
			std::jthread t3(&thread_pool::submit, &tp, std::move(task3));
			std::jthread t4(&thread_pool::submit, &tp, std::move(task4));
			std::jthread t5(&thread_pool::submit, &tp, std::move(task5));
			std::jthread t6(&thread_pool::submit, &tp, std::move(task6));
			std::jthread t7(&thread_pool::submit, &tp, std::move(task7));
			std::jthread t8(&thread_pool::submit, &tp, std::move(task8));
			
			std::cout << std::endl;
			cout_m.unlock();
		}
	}

	cout_m.lock();
	std::cout << std::endl;
	cout_m.unlock();

	{
		thread_pool tp;
		for (int i = 0; i < 5; ++i)
		{
			std::this_thread::sleep_for(1s);
			cout_m.lock();

			std::packaged_task<void()> task1(blue_func);
			std::packaged_task<void()> task2(blue_func);
			std::packaged_task<void()> task3(blue_func);
			std::packaged_task<void()> task4(blue_func);
			std::packaged_task<void()> task5(magenta_func);
			std::packaged_task<void()> task6(magenta_func);
			std::packaged_task<void()> task7(magenta_func);
			std::packaged_task<void()> task8(magenta_func);
			std::packaged_task<void()> task9(red_func);
			std::packaged_task<void()> task10(red_func);
			std::packaged_task<void()> task11(red_func);
			std::packaged_task<void()> task12(red_func);
			std::packaged_task<void()> task13(green_func);
			std::packaged_task<void()> task14(green_func);
			std::packaged_task<void()> task15(green_func);
			std::packaged_task<void()> task16(green_func);
			std::jthread t1(&thread_pool::submit, &tp, std::move(task1));
			std::jthread t2(&thread_pool::submit, &tp, std::move(task2));
			std::jthread t3(&thread_pool::submit, &tp, std::move(task3));
			std::jthread t4(&thread_pool::submit, &tp, std::move(task4));
			std::jthread t5(&thread_pool::submit, &tp, std::move(task5));
			std::jthread t6(&thread_pool::submit, &tp, std::move(task6));
			std::jthread t7(&thread_pool::submit, &tp, std::move(task7));
			std::jthread t8(&thread_pool::submit, &tp, std::move(task8));
			std::jthread t9(&thread_pool::submit, &tp, std::move(task9));
			std::jthread t10(&thread_pool::submit, &tp, std::move(task10));
			std::jthread t11(&thread_pool::submit, &tp, std::move(task11));
			std::jthread t12(&thread_pool::submit, &tp, std::move(task12));
			std::jthread t13(&thread_pool::submit, &tp, std::move(task13));
			std::jthread t14(&thread_pool::submit, &tp, std::move(task14));
			std::jthread t15(&thread_pool::submit, &tp, std::move(task15));
			std::jthread t16(&thread_pool::submit, &tp, std::move(task16));

			std::cout << std::endl;
			cout_m.unlock();
		}
	}
	return 0;
}

