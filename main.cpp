#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include<ctime>
#include<cstdlib>
using namespace std;

// file code sử dụng


long long random(long long min, long long max) {
    return min + rand() % (max - min + 1);
}

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int check_bit_length( long long n) {
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


    unsigned int mod_power(unsigned int a, unsigned int b, unsigned int p);
    void fermat_testing();



};

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}


unsigned int RSA_Cryptography::mod_power(unsigned int a, unsigned int b, unsigned int p) {
    if (b == 1) {
        return a % p;
    }
    else {
        int x = mod_power(a, b / 2, p);
        if ((b % 2) == 0) { // b is even
            return (x * x) % p;
        }
        else {
            return (((x * x) % p) * a) % p;
        }
    }
}
void RSA_Cryptography::fermat_testing() {
    unsigned int a = 2 + rand() % (p - 3);
    if (gcd(a, p) != 1) {
        throw (runtime_error("non prime input error!"));
    }
    else {
        if (mod_power(a, p - 1, p) != 1) {
            throw (runtime_error("non prime input error!"));
        }
    }
    unsigned int b = 2 + rand() % (q - 3);
    if (gcd(b, q) != 1) {
        throw (runtime_error("non prime input error!"));
    }
    else {
        if (mod_power(b, q - 1, q) != 1) {
            throw (runtime_error("non prime input error!"));
        }

    }

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
    // cout << "bit length: 512, 1024, 2048" << endl;
    // cout << "Enter bit length: " << endl;
    // cin >> bit_length;
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
    unsigned int k = 1;

    unsigned int resE = e;
    while (((k * phi_n) + 1) % resE != 0)
        // cout << resE << endl;
        k++;
    d = ((k * phi_n) + 1) / resE;

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
    cout << "fermat_testing" << endl;
    rsa.fermat_testing();
    cout << "RSA" <<endl;
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