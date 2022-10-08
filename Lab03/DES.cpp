#include "DES.h"

DES::DES()
{
  randomKey();
}

void DES::randomKey()
{
  for (size_t i = 0; i < 64; i++)
    key[i] = rand() % 2;
    //key.set(i, rand() % 2);
  /*for (int i = 0; i < 8; i++)
    key[i] = rand() % 256;*/
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
  while (fin.read(tmp, sizeof(char)*8))
  {
    unsigned char uc[8];
    for (int i = 0; i < 8; i++)
      uc[i] = tmp[i];

    //input
    bitset<64> msg_part = 0x0000;
    for (int i = 0; i < 64; i++)
      if (getBit(uc, i))
        msg_part.set(63 - i);
    //cout << msg_part << endl;

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
    int permIP1[64] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
    for (int i = 0; i < 64; i++)
      msg_part[i] = tmp_msg[permIP1[i]-1];

    cout << "Ciphered 8 bytes: " << msg_part << endl;

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
  while (fin.read(tmp, sizeof(char)*8))
  {
    unsigned char uc[8];
    for (int i = 0; i < 8; i++)
      uc[i] = tmp[i];

    //input
    bitset<64> msg_part = 0x0000;
    for (int i = 0; i < 64; i++)
      if (getBit(uc, i))
        msg_part.set(63 - i);
    cout << "Inputed 8 bytes: " << msg_part << endl;

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
    for (int i = 7; i >= 0; i--)
      fout << tmp[i];
  }

  fin.close();
  fout.close();
  return true;
}

/*bool DES::getBit(byte_t ptr[8], int n)
{
  //char c = ptr[n/8];
  //char p = 32 >> n%8;
  //char res = (ptr[n/8]) & (0b10000000 >> n%8);
  return (ptr[n/8]) & (0b10000000 >> n%8);
}*/

bool DES::getBit(unsigned char ptr[8], int n)
{
  /*char c = ptr[n/8];
  char p = 32 >> n%8;
  char res = (ptr[n/8]) & (0b10000000 >> n%8);*/
  return (ptr[n/8]) & (0b10000000 >> n%8);
}

void DES::setBit(byte_t *ptr, int n)
{
  *ptr |= (1 << n);
}

void DES::resetBit(byte_t *ptr, int n)
{
  *ptr &= ~(1 << n);
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
  int permB[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
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
  int shiftS[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
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
    int permCP[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
    for (int j = 0; j < 48; j++)
      round_keys[i][j] = tmp_key[permCP[j]-1];
  }
  cout << "Round keys:" << endl;
  for (int i = 0; i < 16; i ++)
    cout << round_keys[i] << endl;
  cout << endl;
}

bitset<32> DES::feistel(bitset<32> msg, int key_i)
{
  //permutation E
  bitset<48> tmp_msg;
  int permE[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
  for (int i = 0; i < 48; i++)
    tmp_msg[i] = msg[permE[i]-1];

  //XOR
  bitset<48> z = tmp_msg ^ round_keys[key_i];

  int S_blocks[8][4][16] = {
                            {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
                            {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
                            {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
                            {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
                            {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
                            {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
                            {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
                            {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
                           };

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
  int permP[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
  for (int i = 0; i < 32; i++)
    res[i] = z[permP[i]-1];

  return res;
}
