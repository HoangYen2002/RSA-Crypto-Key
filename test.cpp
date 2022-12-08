#include<iostream>
#include<string>
#include<vector>
using namespace std;

int get_bits(char c) {
    int bits = 0;
    for (int i = 0; i < 8; i++) {
        if (c & (1 << i)) {
            bits++;
        }
    }
    return bits;
}
int main() {
    char c;
    cin >> c;
    cout << get_bits(c) << endl;
    return 0;

}