#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx; // ���ؽ� ��ü ����
int counter = 0;

void increment() {
	for (int i = 0; i < 1000; ++i) {
		// 1
		mtx.lock(); // �Ӱ� ������ ���� ���� ���
		++counter; // ���� �ڿ��� ����
		mtx.unlock(); // �Ӱ� ������ ����� ��� ����
		
		// 2
		lock_guard<mutex> lock(mtx);
		++counter;
	}
}

int main() {
	thread t1(increment);
	thread t2(increment);

	t1.join();
	t2.join();

	cout << "Final counter value " << counter << endl;

	return 0;
}