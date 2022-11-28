#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
using namespace std;

class RSA_Cryptography {

public:
    unsigned p;
    unsigned q;
    unsigned n; // n = p*q
    unsigned phi_n; // phi_n = (p-1)*(q-1)
    unsigned e; // e < phi_n; e and phi_n co-prime
    unsigned d; // (e*d) mod phi_n = 1

    void check_primality();
    void inputKey();
    unsigned calN();
    unsigned calPhi_n();
    unsigned calE();
    unsigned calD();

    unsigned encryption();
    unsigned decryption();

};

void RSA_Cryptography::inputKey() {
    cout << "Enter Prime number p: " << endl;
    cin >> p;
    cout << "Enter Prime number q: " << endl;
    cin >> q;
}

void RSA_Cryptography::check_primality() {
    vector<unsigned> p_factor;
    vector<unsigned> q_factor;
    for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(p)); i++){
        if(p % i == 0){
            p_factor.push_back(i);
            p_factor.push_back(p%i);
        }
    }


    for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(q)); i++){
        if(q % i == 0){
            q_factor.push_back(i);
            q_factor.push_back(q%i);
        }
    }

    if(p_factor.size()!= 0 || q_factor.size()!=0)
        throw (runtime_error("non prime input error!"));
}

unsigned RSA_Cryptography::calN() {
    return p*q;
}

unsigned RSA_Cryptography::calPhi_n() {
    return (p-1)*(q-1);
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

unsigned RSA_Cryptography::calE() {
    unsigned i =2;

    while (gcd(i,phi_n) != 1)
        i++;
    e = i;

    if( e >= phi_n )
        throw (runtime_error("e is greater or equal to phi_n"));
}

unsigned RSA_Cryptography::calD() {
    unsigned k=1;

    while (((k * phi_n) + 1) % e != 0)
        k++;
    d = ((k*phi_n) + 1) / e;

    return d;
}

unsigned RSA_Cryptography::encryption() {
    unsigned c = 1;
    unsigned resC = 1;
    unsigned resN = 0;
    resN = calN();
    for (unsigned m = 2; m < resN; m++) {
        c = (pow(m,e));
        resC = c % resN;
    }
    return resC;
}

unsigned RSA_Cryptography::decryption() {
    unsigned resN = 0;
    unsigned resEncrypt_C = 0;
    unsigned m = 0;
    unsigned resM = 0;
    resN = calN();
    resEncrypt_C = encryption();
    for (resEncrypt_C; resEncrypt_C < resN; resEncrypt_C++) {
        m = (pow(resEncrypt_C,d));
        resM = m % resN;
    }
    return resM;
}

int main() {
    try {
        RSA_Cryptography rsa;
        rsa.inputKey();
        rsa.check_primality();
        cout << "Result of n = p*q : " << rsa.calN() << endl;
        cout << "Result of phi_n = (p - 1) * (q - 1) : " << rsa.calPhi_n() << endl;
        cout << "Result of e : " << rsa.calE() << endl;
        cout << "Result of d as e*d = 1 mod n : " << rsa.calD() << endl;
        cout << "Encryption: " << rsa.encryption() << endl;
        cout << "Decryption: " << rsa.decryption() << endl;
    }
    catch (runtime_error &error) {
        cout << error.what() << endl;
    }
    return 0;
}
