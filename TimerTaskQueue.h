#pragma once

#include "TimerCallbackInterface.h"
#include "Timer.h"
#include "Hash_Map.h"
#include <iostream>


class TimerTaskQueue : public TimerCallbackInterface
{
private:
	static TimerTaskQueue* instance;
	stdext::hash_map<int, void(*)()> queueMap;
	std::chrono::steady_clock::time_point start;
	Timer* t = nullptr;
	bool loopPause = false;
	bool loopPauseReset = false;
	int loopCount = 0;
	int maxLoopCount = 1000;
	int baseMicrosecconds = 1000;
	void startTimer();
	TimerTaskQueue();
	~TimerTaskQueue();
public:

	void timerCallback();
	static TimerTaskQueue* getInstance();
	bool registerTask(int delayPeriod, void(*callbackFunc)());
	bool unregisterTask(int delayPeriod);
	int getQueueSize();
	void print();

	virtual void callback() override {
		if (!loopPauseReset && !loopPause) {
			this->timerCallback();
		}
	};
};

TimerTaskQueue* TimerTaskQueue::instance = 0;

void TimerTaskQueue::timerCallback() {
	loopCount++;

	try
	{
		if (this->queueMap.size() > 0) {
				for (auto& p : this->queueMap)
				{
					if (loopPauseReset) {
						break;
						return;
					} else {
						if (this->loopCount % p.first == 0) {
								p.second();
						}
					}
				}
			}
		
		if (loopCount == maxLoopCount) {
			loopCount = 0;
		}
		loopPauseReset = false;
		return;
	}
	catch (...)
	{
		std::cout << "OMG! an unexpected exception has been caught" << std::endl;
		throw("fdf");
	}
	return;
}

void TimerTaskQueue::startTimer() {
	this->start = std::chrono::steady_clock::now();
	t = new Timer(this, baseMicrosecconds);
	t->startThread();
}

TimerTaskQueue::TimerTaskQueue() {
	startTimer();
}

TimerTaskQueue::~TimerTaskQueue()
{
}

TimerTaskQueue* TimerTaskQueue::getInstance()
{
	if (instance == 0)
	{
		instance = new TimerTaskQueue();
	}

	return instance;
}

bool TimerTaskQueue::registerTask(int delayPeriod, void(*callbackFunc)())
{
	if (delayPeriod > maxLoopCount) {
		maxLoopCount = delayPeriod;
	}
	if (queueMap.find(delayPeriod) == queueMap.end()) {
		queueMap.insert(std::pair<int, void(*)()>(delayPeriod, callbackFunc));
		std::cout << "Registered Timer Task in queue with delay period of: " << delayPeriod << std::endl;
		return true;
	}
	else {
		std::cout << "Faild to Register Timer Task in queue with delay period of: " << delayPeriod << std::endl;
		return false;
	}
}

bool TimerTaskQueue::unregisterTask(int delayPeriod)
{
	loopPauseReset = true;
	loopPause = true;
	if (queueMap.find(delayPeriod) == queueMap.end()) {
		std::cout << "Faild to Unregister Timer Task in queue with delay period of: " << delayPeriod << std::endl;
		loopPause = false;
		return false;
	}
	else {
		queueMap.erase(delayPeriod);
		std::cout << "Unregistered Timer Task in queue with delay period of: " << delayPeriod << std::endl;
		loopPause = false;
		return true;
	}
}

int TimerTaskQueue::getQueueSize()
{
	return this->queueMap.size();
}

void TimerTaskQueue::print()
{
	for (const auto& p : this->queueMap)
	{
		std::cout << p.first << '\t' << p.second << std::endl;
	}
}


/* Test Code

using namespace std;
auto start = std::chrono::steady_clock::now();

ConsoleDisplayTable cdt;
int loopCount1 = 0;
int loopCount2 = 0;
int loopCount3 = 0;
std::thread t;
TimerTaskQueue* ttq;
int main()
{

	std::thread t([]() {
		ttq = TimerTaskQueue::getInstance();
		//cdt.add(1, "thread function: ");
		cdt.add(4, "elapsed time t?: " + std::to_string(0));
		cdt.add(3, "elapsed time t?: " + std::to_string(0));
		cdt.add(2, "elapsed time t?: " + std::to_string(0));

		ttq->registerTask(100, []() -> void {
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			if (elapsed_seconds.count() > 3) {
				if (++loopCount1 % 10 == 0) {
					cdt.add(2, "elapsed time t100: " + std::to_string(++loopCount1));
				}
				//cdt.add(2, "elapsed time t100: " + std::to_string(elapsed_seconds.count()) + "s");
			}
			});

		ttq->registerTask(500, []() -> void {
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			if (elapsed_seconds.count() > 3) {
				if (++loopCount1 % 2 == 0) {
					cdt.add(3, "elapsed time t500: " + std::to_string(++loopCount2));
				}
				//cdt.add(3, "elapsed time t500: " + std::to_string(elapsed_seconds.count()) + "s");
			}
			});

		ttq->registerTask(1000, []() -> void {

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			if (elapsed_seconds.count() > 3) {
				cdt.add(4, "elapsed time t1000: " + std::to_string(++loopCount3));
				//cdt.add(4, "elapsed time t1000: " + std::to_string(elapsed_seconds.count()) + "s");
			}if (elapsed_seconds.count() > 5 && elapsed_seconds.count() < 16) {
				//cdt.remove(1);
			}
			if (elapsed_seconds.count() > 21 && elapsed_seconds.count() < 35) {
				//cdt.add(1, "thread function: ");
			}
			});

		while (true) {
		}
		});
	t.join();


	return 0;

}

*/