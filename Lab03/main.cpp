#include <iostream>
#include <bitset>

#include "DES.h"

using namespace std;

#define N 8

int main()
{
  /*bitset<N> key1;
  bitset<N> key2;
  for (size_t i = 0; i < N; i++)
  {
    key1[i] = rand() % 2;
    key2[i] = rand() % 2;
  }
  cout << key1 << endl;
  cout << key2 << endl;
  bitset<N> key3 =  key1 ^ key2;
  cout << key3 << endl;*/

  DES alg;

  //alg.randomKey();

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
