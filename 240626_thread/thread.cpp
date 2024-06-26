// thread

#include <iostream>
#include <string>
#include <vector>
#include <thread>

using namespace std;

#define N 10
#define T 5

void printNum(int threadID) {
	for (int i = 1; i < N + 1; i++) {
		
		cout << "thread " << threadID << " 이 출력합니동동이 : " << i << endl;
	}
}

int main() {

	vector<thread> th_vec;

	th_vec.resize(T);

	for (int t = 0; t < T; t++) {

		th_vec[t] = thread(printNum, t + 1); // t + 1은 threadID로 전달

		//solution 2
		//th_vec.emplace_back(printNum,t + 1); // t + 1은 threadID로 전달
	}
	for (int t = 0; t < T; t++) {

		th_vec[t].join();
	}
	
	return 0;

}