#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <random>

using namespace std;

bool isPrime = true;


class RSA_Cryptography {

public:
    unsigned int p;
    unsigned int q;
    unsigned int n; // n = p*q
    unsigned int phi_n; // phi_n = (p-1)*(q-1)
    unsigned int e; // e < phi_n; e and phi_n co-primen
    unsigned int d; // (e*d) mod phi_n = 1

    //void check_primality();
    //void inputKey();
    unsigned int mod_power(unsigned int a, unsigned int b, unsigned int p);
    void fermat_testing();
    unsigned int calN();
    unsigned int calPhi_n();
    unsigned int calE();
    unsigned int calD();

    bool checkPrime(unsigned int num);
    unsigned int encryption();
    unsigned int decryption();
    void random_Num(unsigned int e, unsigned int phi_n, int count);

};
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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
    unsigned int p, q;
    cout << "Enter Prime number p: " << endl;
    cin >> p;
    cout << "Enter Prime number q: " << endl;
    cin >> q;

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
//void RSA_Cryptography::check_primality() {
//    vector<unsigned int> p_factor;
//    vector<unsigned int> q_factor;
//    for (unsigned int i = 2; i <= static_cast<unsigned int>(sqrt(p)); i++) {
//        if (p % i == 0) {
//            p_factor.push_back(i);
//            p_factor.push_back(p % i);
//        }
//    }
//
//
//    for (unsigned int i = 2; i <= static_cast<unsigned int>(sqrt(q)); i++) {
//        if (q % i == 0) {
//            q_factor.push_back(i);
//            q_factor.push_back(q % i);
//        }
//    }
//
//    if (p_factor.size() != 0 || q_factor.size() != 0)
//        throw (runtime_error("non prime input error!"));
//}

unsigned int RSA_Cryptography::calN() {
    return p * q;
}

unsigned int RSA_Cryptography::calPhi_n() {
    return (p - 1) * (q - 1);
}


unsigned int RSA_Cryptography::calE() {
    unsigned int i = 2;
    while (gcd(i, phi_n) != 1)
        i++;
    e = i;
    return e;
}


unsigned int RSA_Cryptography::calD() {
    unsigned int k = 1;

    unsigned int resE = calE();

    while (((k * phi_n) + 1) % resE != 0)
        // cout << resE << endl;
        k++;
    d = ((k * phi_n) + 1) / resE;

    return d;
}

unsigned int RSA_Cryptography::encryption() {
    unsigned int c = 1;
    unsigned int resC = 1;
    unsigned int resN = 0;
    resN = calN();
    for (unsigned int m = 2; m < resN; m++) {
        c = (pow(m, e));
        resC = fmod(c, resN);
    }
    return resC;
}


unsigned int RSA_Cryptography::decryption() {
    unsigned int resN = 0;
    unsigned int resEncrypt_C = 0;
    unsigned int m = 0;
    unsigned int resM = 0;
    resN = calN();
    resEncrypt_C = encryption();
    for (resEncrypt_C; resEncrypt_C < resN; resEncrypt_C++) {
        m = (pow(resEncrypt_C, d));
        resM = fmod(m, resN);
    }
    return resM;
}

int main() {


    try {

        RSA_Cryptography rsa;
        //rsa.inputKey();
        rsa.fermat_testing();

        cout << "Result of n = p*q : " << rsa.calN() << endl;
        cout << "Result of phi_n = (p - 1) * (q - 1) : " << rsa.calPhi_n() << endl;
        cout << "Result of e : " << rsa.calE() << endl;
        cout << "Result of d as e*d = 1 mod n : " << rsa.calD() << endl;
        cout << "Encryption: " << rsa.encryption() << endl;
        cout << "Decryption: " << rsa.decryption() << endl;


    }
    catch (runtime_error& error) {
        cout << error.what() << endl;
    }


    return 0;
}


/*
Enter Prime number p:
3
Enter Prime number q:
97
Result of n = p*q : 291
Result of phi_n = (p - 1) * (q - 1) : 192
Result of e : 7
Result of d as e*d = 1 mod n : 6990043
Encryption: 290
Decryption: 228

*/