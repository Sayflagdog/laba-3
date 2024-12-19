#include <iostream>
using namespace std;

void dep(double &balance, double amount) {
    balance += amount;
    cout << "пополнено на " << amount << ". баланс: " << balance << endl;
}

void popa(double &balance, double amount) {
    if (amount > balance) {
        cout << "недостаточно средств(((" << endl;
    } else {
        balance -= amount;
        cout << "снято " << amount << ". баланс: " << balance << endl;
    }
}

void ubivalka(double &balance, double interestRate) {
    double interest = balance * (interestRate / 100);
    dep(balance, interest);
    cout << "начислены проценты: " << interest << ". новый баланс: " << balance << endl;
}

int main() {
    double balance1 = 1337.0;

    double balance2 = 228.0;
    double interestRate = 5.0;

    cout << "\nоперации с обычным счётом:" << endl;
    dep(balance1, 500.0);
    popa(balance1, 200.0);


    cout << "\nоперации с сберегательным счётом:" << endl;
    dep(balance2, 500.0);
    popa(balance2, 1000.0);
    ubivalka(balance2, interestRate);

    return 0;
}
