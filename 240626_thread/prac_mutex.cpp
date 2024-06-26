#include <iostream>
#include <thread>
#include <mutex>

using namespace std;


class BankAccount {

public:
	BankAccount() {};

	void deposit(int amount);
	void withdraw(int amount);

private:
	int balance = 1000;
	mutable mutex mtx; // mutex에 대한 권한을 lock이라는 객체가 가져간 것. 
	//주고 받고 사용(공유)할 때 global에 사용하지만, 하나의 클래스에만 사용할 떄는 클래스 내부에 선언하는 것이 좋음.
};

void BankAccount::deposit(int amount) {
	mtx.lock();
	balance += amount;
	cout << "계좌의 잔액은 " << balance << " 원 입니다." << endl;
	mtx.unlock();

}
void BankAccount::withdraw(int amount) {
	mtx.lock(); 
	balance -= amount;
	cout << "계좌의 잔액은 " << balance << " 원 입니다." << endl;
	mtx.unlock(); 
	
}

// count 횟수만큼 amount를 입금(deposit)
void deposit_iter(BankAccount& ba, int amount, int count) {
	for (int i = 0; i < count; i++) {
		ba.deposit(amount);
	}
}

// count 횟수만큼 amount를 출금(withdraw)
void withdraw_iter(BankAccount& ba, int amount, int count) {
	for (int i = 0; i < count; i++) {
		ba.withdraw(amount);
	}
}

int main()
{

	BankAccount BA;
	
	thread t1(deposit_iter, ref(BA), 100, 100);
	thread t2(withdraw_iter, ref(BA), 100, 100);

	t1.join();
	t2.join();

	return 0;
}