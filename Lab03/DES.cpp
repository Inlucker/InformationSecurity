#include "DES.h"

#include <iostream>

DES::DES()
{
  randomKey();
}

void DES::randomKey()
{
  for (size_t i = 0; i < 64; i++)
    key[i] = rand() % 2;
  //cout << key << endl;
  genRoundKeys();
}

bool DES::encipher(string input_file_name, string output_file_name)
{
  ifstream fin(input_file_name, ios::in | ios::binary);
  if (!fin)
    return false;

  ofstream fout;
  if (output_file_name == "default_file_name")
    fout.open("ciphered_" + input_file_name, ios::out | ios::binary);
  else
    fout.open(output_file_name, ios::out | ios::binary);

  if (!fout)
  {
    fin.close();
    return false;
  }

  byte_t tmp[8];
  while (!fin.eof())
  //while (fin.read(tmp, sizeof(char)*8))
  {
    if (!fin.read(tmp, sizeof(char)*8))
    {
      size_t extracted = fin.gcount();
      if (!extracted)
        break;
      int flag = 8-extracted;
      for (int i = extracted; i < 8; i++)
        tmp[i] = flag;
    }
    unsigned char uc[8];
    for (int i = 0; i < 8; i++)
      uc[i] = tmp[i];

    //input
    bitset<64> msg_part = 0x0000;
    for (int i = 0; i < 64; i++)
      if (getBit(uc, i))
        msg_part.set(63 - i);

    //encipher
    //permutation IP
    bitset<64> tmp_msg = msg_part;
    for (int i = 0; i < 64; i++)
      msg_part[i] = tmp_msg[permIP[i]-1];

    //split
    bitset<32> left;
    bitset<32> right;
    for (int i = 0; i < 32; i++)
      left[i] = msg_part[i];
    for (int i = 32; i < 64; i++)
      right[i-32] = msg_part[i];

    //cycle
    for (int i = 0; i < 16; i++)
    {
      bitset<32> tmp = right;

      right = left ^ feistel(right, i);
      left = tmp;
    }

    //gluing
    for (int i = 0; i < 32; i++)
    {
      msg_part[i] = left[i];
      msg_part[32+i] = right[i];
    }

    //permutation IP-1
    tmp_msg = msg_part;
    for (int i = 0; i < 64; i++)
      msg_part[i] = tmp_msg[permIP1[i]-1];

    //cout << "Ciphered 8 bytes: " << msg_part << endl;

    //output
    for (int i = 0; i < 8; i++)
      tmp[i] = bitsToChar(msg_part, i);
    for (int i = 7; i >= 0; i--)
      fout << tmp[i];
  }

  fin.close();
  fout.close();
  return true;
}

bool DES::decipher(string input_file_name, string output_file_name)
{
  ifstream fin_size(input_file_name, ios::binary | ios::ate);
  int file_size = fin_size.tellg();
  fin_size.close();
  //cout << file_size;
  ifstream fin(input_file_name, ios::in | ios::binary);

  if (!fin)
    return false;

  ofstream fout;
  if (output_file_name == "default_file_name")
    fout.open("deciphered_" + input_file_name, ios::out | ios::binary);
  else
    fout.open(output_file_name, ios::out | ios::binary);

  if (!fout)
  {
    fin.close();
    return false;
  }

  byte_t tmp[8];
  //while (!fin.eof())
  while (fin.read(tmp, sizeof(char)*8))
  {
    //fin.read(tmp, sizeof(char)*8);
    //cout << fin.tellg() << endl;
    unsigned char uc[8];
    for (int i = 0; i < 8; i++)
      uc[i] = tmp[i];

    //input
    bitset<64> msg_part = 0x0000;
    for (int i = 0; i < 64; i++)
      if (getBit(uc, i))
        msg_part.set(63 - i);
    //cout << "Inputed 8 bytes: " << msg_part << endl;

    //encipher
    //permutation IP
    bitset<64> tmp_msg = msg_part;
    int permIP[64] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    for (int i = 0; i < 64; i++)
      msg_part[i] = tmp_msg[permIP[i]-1];

    //split
    bitset<32> left;
    bitset<32> right;
    for (int i = 0; i < 32; i++)
      left[i] = msg_part[i];
    for (int i = 32; i < 64; i++)
      right[i-32] = msg_part[i];

    //cycle
    for (int i = 15; i >= 0; i--)
    {
      bitset<32> tmp = left;

      left = right ^ feistel(left, i);
      right = tmp;
    }

    //gluing
    for (int i = 0; i < 32; i++)
    {
      msg_part[i] = left[i];
      msg_part[32+i] = right[i];
    }

    //permutation IP-1
    tmp_msg = msg_part;
    int permIP1[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
    for (int i = 0; i < 64; i++)
      msg_part[i] = tmp_msg[permIP1[i]-1];

    //output
    for (int i = 0; i < 8; i++)
      tmp[i] = bitsToChar(msg_part, i);
    //checkForExtraChars
    if (fin.tellg() >= file_size && tmp[0] >= 1 && tmp[0] <= 8)
    {
      bool flag = true;
      for (int i = 1; i < tmp[0]; i++)
        if (tmp[i] != tmp[0])
          flag = false;

      if (flag)
        for (int i = 7; i >= tmp[0]; i--)
          fout << tmp[i];
      else
        for (int i = 7; i >= 0; i--)
          fout << tmp[i];
    }
    else
      for (int i = 7; i >= 0; i--)
        fout << tmp[i];
  }

  fin.close();
  fout.close();
  return true;
}

bool DES::getBit(unsigned char ptr[8], int n)
{
  return (ptr[n/8]) & (0b10000000 >> n%8);
}

char DES::bitsToChar(bitset<64> bits, int n)
{
  char res = 0;
  for (int i = 0; i < 8; i++)
  {
    if (bits[n*8+i])
    {
      int tmp = 1;
      for (int j = 0; j < i; j++)
        tmp *= 2;
      res += tmp;
    }
  }
  return res;
}

void DES::genRoundKeys()
{
  //permutation B
  bitset<56> tmp_key;
  for (int i = 0; i < 56; i++)
    tmp_key[i] = key[permB[i]-1];

  //split
  bitset<28> C0;
  bitset<28> D0;
  for (int i = 0; i < 28; i++)
    C0[i] = tmp_key[i];
  for (int i = 28; i < 56; i++)
    D0[i-28] = tmp_key[i];

  //shift S
  for (int i = 0; i < 16; i++)
  {
    for (int j = 0; j < shiftS[i]; j++)
    {
      bitset<1> tmp_bit;
      tmp_bit[0] = C0[27];
      C0 = C0 << 1;
      C0[0] = tmp_bit[0];

      tmp_bit[0] = D0[27];
      D0 = D0 << 1;
      D0[0] = tmp_bit[0];
    }

    //gluing
    for (int i = 0; i < 28; i++)
    {
      tmp_key[i] = C0[i];
      tmp_key[28+i] = D0[i];
    }

    //permutation CP
    for (int j = 0; j < 48; j++)
      round_keys[i][j] = tmp_key[permCP[j]-1];
  }
  /*cout << "Round keys:" << endl;
  for (int i = 0; i < 16; i ++)
    cout << round_keys[i] << endl;
  cout << endl;*/
}

bitset<32> DES::feistel(bitset<32> msg, int key_i)
{
  //permutation E
  bitset<48> tmp_msg;
  for (int i = 0; i < 48; i++)
    tmp_msg[i] = msg[permE[i]-1];

  //XOR
  bitset<48> z = tmp_msg ^ round_keys[key_i];

  for (int i = 0; i < 8; i++)
  {
    bitset<2> x_bits;
    x_bits[0] = z[i*4];
    x_bits[1] = z[i*4+6];

    bitset<4> y_bits;
    for (int j = 0; j < 4; j++)
      y_bits[j] = z[i*4+j+1];

    unsigned long x = x_bits.to_ulong();
    unsigned long y = y_bits.to_ulong();

    bitset<8> byte = S_blocks[i][x][y];
    for (int j = 0; j < 8; j++)
      z[i*4+j] = byte[j];
  }

  //permutation P
  bitset<32> res;
  for (int i = 0; i < 32; i++)
    res[i] = z[permP[i]-1];

  return res;
}
