// print size bits of decimal

#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>

using namespace std;

bool isPrime(long long n) {
    if (n < 2) return false;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}
int check_bit_length(long long n) {
    int bits = 0;
    while (n > 0) {
        n >>= 1;
        bits++;
    }
    return bits;
}



int main() {

    long long n = 100000000;
    while(!isPrime(n)) {
        n++;
    }
    cout << n << endl;
    cout << check_bit_length(n) << endl;



}
//10000000000000061
