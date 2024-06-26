#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

class BankAccount {

public:
	BankAccount() {};

	void deposit(int amount);
	void withdraw(int amount);

private:
	int balance = 1000;
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