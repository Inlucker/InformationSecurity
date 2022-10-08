#ifndef DES_H
#define DES_H

#include <iostream>
#include <string>
#include <fstream>
#include <random>
//#include <map>
#include <bitset>

using namespace std;

typedef char byte_t;

class DES
{
public:
  DES();

  void randomKey();
  bool encipher(string input_file_name, string output_file_name = "default_file_name");
  bool decipher(string input_file_name, string output_file_name = "default_file_name");

private:
  //bool getBit(byte_t ptr[], int n);
  bool getBit(unsigned char ptr[], int n);
  void setBit(byte_t* ptr, int n);
  void resetBit(byte_t* ptr, int n);
  char bitsToChar(bitset<64> bits, int n);
  void genRoundKeys();
  bitset<32> feistel(bitset<32> msg_part, int key_i);

private:
  /*byte_t key[8];
  byte_t round_keys[16][6];
  byte_t msg_part[8];*/
  bitset<64> key = 0x0000;
  bitset<48> round_keys[16];
  //bitset<64> msg_part = 0x0000;

};

#endif // DES_H
