#include <iostream>
#include <thread>

using namespace std;

class BankAccount {

public:
	BankAccount() {};

	void setBalance(int seed);
	void deposit(int amount);
	void withdraw(int amount);

private:
	atomic<int> balance;
	
};
void BankAccount::setBalance(int seed) {
	balance.store(seed);
}
void BankAccount::deposit(int amount) {
	balance += amount;
	cout << "계좌의 잔액은 " << balance << " 원 입니다." << endl;

}
void BankAccount::withdraw(int amount) {
	balance -= amount;
	cout << "계좌의 잔액은 " << balance << " 원 입니다." << endl;

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

	return 0;
}