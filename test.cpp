#include <iostream>
#include <stdio.h>
#include <limits.h>
using namespace std;

void print(unsigned char byte)
{
    for (int i = 7; i >= 0; i--) {
        int b = byte >> i;
        if (b & 1)
            cout << "1";
        else
            cout << "0";
    }
}

string convert_decimal_to_binary(unsigned char number)
{
    string binary = "";
    unsigned char mask = 1 << 7;
    for (int i = 0; i < 8; i++) {
        if (number & mask) {
            cout << "1";
            binary += "1";
        }
        else {
            cout << "0";
            binary += "0";
        }
        mask >>= 1;
    }
    cout << endl;
    return binary;
}

void convert_binary_to_decimal(string binary)
{
    unsigned char decimal = 0;
    for (int i = 0; i < binary.length(); i++) {
        decimal <<= 1;
        if (binary[i] == '1') {
            decimal |= 1;
        }
    }
    cout << "decimal: " << (int)decimal << endl;
}
void convert_binary_to_bits(string binary) {
    string bits;
    for (int i = 0; i < binary.length(); i++) {
        if (binary[i] == '1') {
            bits += "0";
        }
        else {
            bits += "1";
        }
    }
    cout << "bits: " << bits.length() << endl;
}


int main() {
    int a = 0;
    cout << "Enter a number: " << a << endl;

    cout << "Binary: ";
    string binary = convert_decimal_to_binary(a);
    convert_binary_to_decimal(binary);
    convert_binary_to_bits(binary);

}