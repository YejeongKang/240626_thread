#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

class BankAccount {

public:
	BankAccount() {};

	void setBalance(int seed);
	void deposit(int amount);
	void withdraw(int amount);
	int getBalance();

private:
	atomic<int> balance;
	mutable mutex mtx;
};

void BankAccount::setBalance(int seed) {
	balance.store(seed);
}
void BankAccount::deposit(int amount) {
	balance += amount;
	//balance.fetch_add(amount);
	mtx.lock();
	cout << "Balance : " << balance << endl;
	mtx.unlock();
}
void BankAccount::withdraw(int amount) {
	balance -= amount;
	//balance.fetch_add(-amount); 
	mtx.lock();
	cout << "Balance : " << balance << endl;
	mtx.unlock();
}
int BankAccount::getBalance() {
	return balance;
}


void setNum(BankAccount& ba, int seed) {
	ba.setBalance(seed);
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

	thread t0(setNum, ref(BA), 1000);
	thread t1(deposit_iter, ref(BA), 100, 100);
	thread t2(withdraw_iter, ref(BA), 100, 100);

	t0.join();
	t1.join();
	t2.join();

	cout << "Final Balance : " << BA.getBalance();

	return 0;
}