
// C++ program to demonstrate that we can get part of a
// bit string in bitset.
#include <bitset>
#include <string>
#include <iostream>

using namespace std;

int main()
{
  string bit_string = "110010";
  bitset<8> b1(bit_string);             // [0, 0, 1, 1, 0, 0, 1, 0]
 
  // string from position 2 till end
  bitset<8> b2(bit_string, 2);      // [0, 0, 0, 0, 0, 0, 1, 0]
 
  // string from position 2 till next 3 positions
  bitset<8> b3(bit_string, 2, 3);   // [0, 0, 0, 0, 0, 0, 0, 1]
   
  cout << b1 << '\n' << b2 << '\n' << b3 << '\n';
 
  return 0;
}