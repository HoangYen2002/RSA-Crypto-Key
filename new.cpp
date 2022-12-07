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

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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
    int encryption();
    int decryption();

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
    while (true) {
        if (gcd(e, phi_n) == 1) {
            break;
        }
        e = random(1, phi_n);
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

int RSA_Cryptography::encryption() {
    int c = 1;
    int resC = 1;
    int resN = 0;
    resN = n;
    for(int m = 2; m <= resN; m++) {
        c = pow(m, e);
        resC = c % resN;
    }
    return resC; 
}

int RSA_Cryptography::decryption() {
    int resN = 0;
    int resEncrypt_C = 0;
    int m = 0;
    int resM = 0;
    resN = n;
    resEncrypt_C = encryption();
    for (resEncrypt_C; resEncrypt_C < resN; resEncrypt_C++) {
        m = (pow(resEncrypt_C, d));
        resM = m % resN;
    }
    return resM;
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



// p = 3
// q = 97
// n = 291
// phi_n = 192
// e = 1
// d = 193


// p = 3
// q = 97
// n = 291
// phi_n = 192
// e = 143
// d = 47