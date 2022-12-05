// print size bits of decimal

#include<iostream>
#include<cmath>

using namespace std;

int get_bits(unsigned int number) {
    long bits = 0;
    while (number > 0) {
        number >>= 1;
        bits++;
    }
    return bits;
}

int main() {

    unsigned int* p = new unsigned int;
    *p = 0;
    while (get_bits(*p) != 32) {
        // system("clear");
        cout << "Enter a number: ";
        cin >> *p;
        cout << "Bits: " << get_bits(*p) << endl;
        *p += 1;
    }
    return 0;
}