#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include<ctime>
#include<cstdlib>
using namespace std;



long long random(long long min, long long max) {
    return min + rand() % (max - min + 1);
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int check_bit_length(long long n) {
    int bits = 0;
    while (n > 0) {
        n >>= 1;
        bits++;
    }
    return bits;
}

class RSA_Cryptography
{
private:
    long long p; // p is prime
    long long q; // q is prime
    long long n; // n = p*q
    long long phi_n; // phi_n = (p-1)*(q-1)
    long long e; // e < phi_n; e and phi_n co-prime
    long long d; // (e*d) = 1 mod phi_n
    int bit_length;

public:
    RSA_Cryptography();
    RSA_Cryptography(long long p, long long q);
    long long get_p();
    long long get_q();
    int get_bit_length();
    void set_p(long long p);
    void set_q(long long q);
    void set_bit_length(int bit_length);



    void input();
    void calculate();
    void calculate_e();
    void calculate_d();
    void output();
    long long encryption();
    long long decryption();




};

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i <= sqrt(n); i++) {
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
    bit_length = 8;
}
RSA_Cryptography::RSA_Cryptography(long long p, long long q) {
    this->p = p;
    this->q = q;
    n = p * q;
    phi_n = (p - 1) * (q - 1);
    e = random(1, phi_n);
    d = 0;
    bit_length = 8;
}

long long RSA_Cryptography::get_p() {
    return p;
}
long long RSA_Cryptography::get_q() {
    return q;
}
int RSA_Cryptography::get_bit_length() {
    return bit_length;
}
void RSA_Cryptography::set_p(long long p) {
    this->p = p;
}
void RSA_Cryptography::set_q(long long q) {
    this->q = q;
}
void RSA_Cryptography::set_bit_length(int bit_length) {
    this->bit_length = bit_length;
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
    cout << "bit length: 512, 1024, 2048" << endl;
    cout << "Enter bit length: " << endl;
    cin >> bit_length;
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
    long long k = 1;
    // (e*d) = 1 mod phi_n && bit length of d = bit length
    while (true) {
        if ((k * phi_n + 1) % e == 0) {
            d = (k * phi_n + 1) / e;
            if (check_bit_length(d) == bit_length) {
                break;
            }
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

long long RSA_Cryptography::encryption() {
    long long c = 1;
    long long resC = 1;
    long long resN = 0;
    resN = n;
    for (long long m = 2; m <= resN; m++) {
        c = pow(m, e);
        resC = c % resN;
    }
    return resC;
}

long long RSA_Cryptography::decryption() {
    long long resN = 0;
    long long resEncrypt_C = 0;
    long long m = 0;
    long long resM = 0;
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
    cout << "Encryption: " << encryption() << endl;
    cout << "Decryption: " << decryption() << endl;
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