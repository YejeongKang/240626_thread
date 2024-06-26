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
	mutable mutex mtx; // mutex�� ���� ������ lock�̶�� ��ü�� ������ ��. 
	//�ְ� �ް� ���(����)�� �� global�� ���������, �ϳ��� Ŭ�������� ����� ���� Ŭ���� ���ο� �����ϴ� ���� ����.
};

void BankAccount::deposit(int amount) {
	mtx.lock();
	balance += amount;
	cout << "������ �ܾ��� " << balance << " �� �Դϴ�." << endl;
	mtx.unlock();

}
void BankAccount::withdraw(int amount) {
	mtx.lock(); 
	balance -= amount;
	cout << "������ �ܾ��� " << balance << " �� �Դϴ�." << endl;
	mtx.unlock(); 
	
}

// count Ƚ����ŭ amount�� �Ա�(deposit)
void deposit_iter(BankAccount& ba, int amount, int count) {
	for (int i = 0; i < count; i++) {
		ba.deposit(amount);
	}
}

// count Ƚ����ŭ amount�� ���(withdraw)
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