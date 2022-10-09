#include <iostream>
#include <bitset>

#include "DES.h"

using namespace std;

#define N 8

int main()
{
  DES alg;

  string file_name = "text.txt";
  if (alg.encipher(file_name, "ciphered_" + file_name))
    cout << "File " << file_name << " encipered in " << "ciphered_" + file_name << endl;
  else
    cout << "Couldn't encipher file " << file_name << endl;

  if (alg.decipher("ciphered_" + file_name, "deciphered_" + file_name))
    cout << "File " << file_name << " decipered in " << "deciphered_" + file_name << endl;
  else
    cout << "Couldn't decipher file " << file_name << endl;

  return 0;
}
