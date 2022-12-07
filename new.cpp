#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include<ctime>
#include<cstdlib>
using namespace std;

int random(int min, int max) {
    return min + rand() % (max - min + 1);
}


class RSA_Cryptography
{
private:
    int p; // p is prime
    int q; // q is prime
    int n; // n = p*q
    int phi_n; // phi_n = (p-1)*(q-1)
    int e; // e < phi_n; e and phi_n co-prime
    int d; // (e*d) = 1 mod phi_n

public:
    RSA_Cryptography();
    RSA_Cryptography(int p, int q);
    int get_p();
    int get_q();
    void set_p(int p);
    void set_q(int q);
    
    void input();
    void calculate();
    void calculate_e();
    void calculate_d();
    void output();

};

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

RSA_Cryptography::RSA_Cryptography() {
    p = 0;
    q = 0;
    n = 0;
    phi_n = 0;
    e = 0;
    d = 0;
}
RSA_Cryptography::RSA_Cryptography(int p, int q) {
    this->p = p;
    this->q = q;
    n = p * q;
    phi_n = (p - 1) * (q - 1);
    e = random(1, phi_n);
    d = 0;
}

int RSA_Cryptography::get_p() {
    return p;
}
int RSA_Cryptography::get_q() {
    return q;
}
void RSA_Cryptography::set_p(int p) {
    this->p = p;
}
void RSA_Cryptography::set_q(int q) {
    this->q = q;
}
void RSA_Cryptography::input() {
    cout << "Enter Prime number p: " << endl;
    cin >> p;
    while (!isPrime(p)) {
        cout << "p is not prime, please enter again: " << endl;
        cin >> p;
    }
    cout << "Enter Prime number q: " << endl;
    cin >> q;
    while (!isPrime(q)) {
        cout << "q is not prime, please enter again: " << endl;
        cin >> q;
    }
}

void RSA_Cryptography::calculate_e() {
    int i = 1;
    while(gcd(i, phi_n) != 1) {
        i++;
    }
    e = i;
    if (e >= phi_n) {
        throw (runtime_error("e is greater or equal to phi_n"));
    }
}

void RSA_Cryptography::calculate_d() {
    int k = 1;
    while (true) {
        if ((k * phi_n + 1) % e == 0) {
            d = (k * phi_n + 1) / e;
            break;
        }
        k++;
    }
}

void RSA_Cryptography::calculate() {
    n = p * q;
    phi_n = (p - 1) * (q - 1);
    calculate_e();
    calculate_d();
}

void RSA_Cryptography::output() {
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "n = " << n << endl;
    cout << "phi_n = " << phi_n << endl;
    cout << "e = " << e << endl;
    cout << "d = " << d << endl;
}


int main() {
    srand(time(NULL));
    RSA_Cryptography rsa;
    rsa.input();
    cout << rsa.get_p() << endl;
    cout << rsa.get_q() << endl;
    rsa.calculate();
    rsa.output();
    

    return 0;
}

