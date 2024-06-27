#include <iostream>
#include <mutex>
#include <chrono>
#include <thread>

using namespace std;

mutex mtx;
condition_variable cv;
bool alarm_set = false;

void timer(int sec) {
	
	unique_lock<mutex> uniqueLock(mtx, defer_lock);

	this_thread::sleep_for(chrono::seconds(sec));
	
	if (uniqueLock.try_lock()) {

		cout << "Thread acquired the lock." << endl;

		alarm_set = true;

		cv.notify_one();

		cout << "Thread released the lock." << endl;

		uniqueLock.unlock();
	}
	else {

		uniqueLock.lock();
		
		cout << "Thread could not acquire the lock." << endl;

		uniqueLock.unlock();
	}

}

void wait_for_alarm() {

	unique_lock<mutex> uniqueLock(mtx);

	cv.wait(uniqueLock, [] { return alarm_set; }); // timer가 알람을 전달할 때까지 대기

	cout << "Ring Ring Ring ~ Alarm's coming !" << endl;

}

int main() {

	cout << "Waiting for alarm ... ㅠ" << endl;

	thread t1(timer, 10);
	thread t2(wait_for_alarm);

	t1.join();
	t2.join();

	return 0;
}