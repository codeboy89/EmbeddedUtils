#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <thread>	
#include "TimerCallbackInterface.h"

class Timer
{
private:
	std::thread task;
	TimerCallbackInterface* tci;
	bool running = false;
	int delayPeriod = 1;
	int runCount = 0;
	void runFunc() {
		std::cout << "Thread Started with Dealy Period of " << this->delayPeriod << std::endl;
		auto start = std::chrono::steady_clock::now();

		while (running) {
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			if (elapsed_seconds.count() * 1000.0 >= 0.9994) {
				start = std::chrono::steady_clock::now();
				this->tci->callback();
			}
		}
		std::cout << " Thread Stopped" << std::endl;
	}


public:

	Timer(TimerCallbackInterface* timerCallback, int delayPeriod) {
		this->tci = timerCallback;
		this->delayPeriod = delayPeriod;
	}

	void startThread() {
		this->running = true;
		task = std::thread(&Timer::runFunc, this);
		task.detach();
	}

	void stopThread() {
		this->running = false;
	}

};
