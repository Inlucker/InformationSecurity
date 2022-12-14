#include "Rotors.h"

// AbstractRotor
Rotor::Rotor()
{
  for (int i = 0; i < SIZE; i++)
    map[i] = i;
  cur_pos = 0;
}

Rotor::~Rotor() {}

int Rotor::getMapIndex(unsigned char c)
{
  for (int i = 0; i < SIZE; i++)
  {
    if (map[i] == c)
      return i;
  }
  return -1;
}

unsigned char Rotor::getCurChar()
{
  return cur_pos;
}

unsigned char Rotor::forward(unsigned char in, unsigned char prev_char)
{
  unsigned char index = in + (cur_pos - prev_char);
  unsigned char out = map[index];
  return out;
}

unsigned char Rotor::backward(unsigned char in, unsigned char next_char)
{
  in = getMapIndex(in);
  unsigned char out = in - (cur_pos - next_char);
  return out;
}

bool Rotor::rotate()
{
  cur_pos = (cur_pos + 1) % SIZE;
  bool flag = cur_pos == rotate_char;
  return flag;
}

void Rotor::setPos(int pos)
{
  cur_pos = pos;
}

// Rotor1
Rotor1::Rotor1()
{
  for (int i = 0; i < SIZE; i++)
    map[i] = i;
  //random_shuffle(&map[0], &map[SIZE]);
  int array[256] = {205, 240, 162, 226, 237, 136, 227, 152, 188, 102, 193, 124, 244, 219, 71, 150, 246, 108, 94, 17, 175, 47, 64, 66, 65, 7, 222, 76, 138, 99, 77, 81, 192, 155, 56, 39, 25, 3, 151, 101, 61, 68, 172, 167, 24, 160, 97, 19, 179, 180, 198, 33, 21, 224, 197, 15, 120, 196, 239, 44, 83, 38, 46, 103, 84, 95, 213, 200, 170, 23, 70, 149, 163, 148, 251, 186, 211, 189, 100, 42, 191, 52, 72, 53, 67, 215, 245, 207, 144, 146, 45, 181, 93, 147, 153, 80, 116, 114, 49, 4, 88, 16, 90, 127, 255, 202, 85, 55, 178, 221, 229, 10, 13, 105, 177, 58, 0, 60, 234, 34, 50, 141, 242, 156, 134, 28, 176, 118, 48, 1, 210, 6, 187, 119, 243, 128, 232, 166, 5, 236, 137, 73, 253, 217, 214, 212, 69, 111, 79, 184, 51, 87, 216, 135, 168, 158, 249, 92, 35, 182, 107, 235, 126, 31, 2, 254, 133, 233, 18, 201, 174, 8, 159, 82, 37, 113, 9, 63, 41, 104, 59, 26, 231, 145, 89, 122, 110, 142, 86, 164, 29, 30, 169, 154, 223, 112, 140, 78, 75, 220, 238, 54, 143, 195, 131, 130, 228, 139, 121, 109, 12, 161, 125, 57, 74, 190, 250, 171, 209, 199, 40, 123, 204, 247, 183, 173, 98, 185, 208, 248, 241, 14, 27, 203, 218, 230, 43, 96, 22, 194, 129, 11, 115, 165, 32, 132, 91, 36, 157, 117, 225, 206, 20, 106, 62, 252};
  for (int i = 0; i < SIZE; i++)
    map[i] = array[i];

  // ???????????????? ?? ???????????? ????????????
  /*bool flags[SIZE];
  for (int i = 0; i < SIZE; i++)
    flags[i] = false;
  ofstream fout;
  fout.open("Rotor1.txt");
  fout.setf(ios::dec);
  for (int i = 0; i < SIZE; i++)
  {
    if (!flags[map[i]])
      flags[map[i]] = true;
    else
      printf("Rotor error %d ", map[i]);
    fout << dec << +map[i] << endl;
    //fout << dec << +map[i] << ", ";
  }
  fout.close();*/

  cur_pos = 0;
  rotate_char = 'R';
}

Rotor1::Rotor1(int pos) : Rotor1()
{
  cur_pos = pos;
}

// Rotor2
Rotor2::Rotor2()
{
  for (int i = 0; i < SIZE; i++)
    map[i] = i;
  //random_shuffle(&map[0], &map[SIZE]);
  int array[256] = {37, 222, 90, 114, 187, 50, 147, 83, 0, 230, 250, 74, 95, 8, 26, 172, 136, 121, 17, 210, 41, 102, 57, 61, 228, 82, 203, 190, 24, 246, 38, 212, 125, 59, 181, 221, 254, 253, 107, 18, 25, 105, 201, 124, 211, 196, 206, 138, 167, 127, 184, 142, 78, 245, 79, 108, 110, 81, 77, 47, 9, 131, 232, 116, 236, 159, 73, 87, 235, 75, 191, 165, 174, 220, 71, 219, 247, 100, 106, 48, 179, 14, 239, 31, 98, 243, 5, 19, 60, 39, 231, 23, 242, 11, 199, 72, 141, 43, 183, 62, 214, 40, 162, 22, 118, 113, 49, 189, 207, 198, 97, 213, 10, 216, 209, 130, 249, 3, 149, 29, 135, 233, 123, 240, 163, 34, 133, 56, 1, 150, 140, 171, 117, 146, 223, 96, 109, 225, 64, 205, 192, 28, 173, 185, 103, 197, 200, 84, 111, 157, 244, 145, 52, 170, 241, 139, 27, 126, 158, 92, 194, 85, 2, 148, 226, 33, 251, 55, 204, 252, 132, 20, 13, 161, 115, 134, 89, 137, 7, 217, 21, 178, 208, 168, 86, 188, 112, 36, 176, 224, 128, 51, 63, 30, 104, 101, 218, 46, 237, 160, 120, 152, 68, 255, 58, 155, 122, 166, 70, 193, 238, 91, 45, 129, 227, 54, 42, 182, 4, 69, 154, 88, 151, 175, 234, 6, 248, 93, 15, 66, 119, 76, 53, 12, 94, 177, 195, 215, 32, 99, 144, 143, 156, 80, 180, 169, 67, 186, 44, 202, 153, 65, 35, 229, 16, 164};
  for (int i = 0; i < SIZE; i++)
    map[i] = array[i];

  // ???????????????? ?? ???????????? ????????????
  /*bool flags[SIZE];
  for (int i = 0; i < SIZE; i++)
    flags[i] = false;
  ofstream fout;
  fout.open("Rotor2.txt");
  fout.setf(ios::dec);
  for (int i = 0; i < SIZE; i++)
  {
    if (!flags[map[i]])
      flags[map[i]] = true;
    else
      printf("Rotor error %d ", map[i]);
    fout << dec << +map[i] << endl;
    //fout << dec << +map[i] << ", ";
  }
  fout.close();*/

  cur_pos = 0;
  rotate_char = 'F';
}

Rotor2::Rotor2(int pos) : Rotor2()
{
  cur_pos = pos;
}

// Rotor3
Rotor3::Rotor3()
{
  for (int i = 0; i < SIZE; i++)
    map[i] = i;
  //random_shuffle(&map[0], &map[SIZE]);
  int array[256] = {38, 92, 115, 30, 52, 203, 0, 240, 163, 122, 28, 220, 170, 119, 161, 159, 126, 233, 148, 105, 15, 32, 189, 58, 42, 18, 99, 37, 146, 185, 113, 215, 76, 180, 218, 181, 69, 139, 182, 63, 45, 128, 234, 39, 12, 46, 247, 80, 131, 3, 156, 144, 169, 61, 197, 13, 186, 59, 214, 135, 114, 35, 129, 89, 120, 160, 207, 246, 187, 117, 136, 196, 127, 104, 96, 84, 82, 230, 43, 223, 225, 40, 235, 27, 47, 97, 206, 199, 26, 29, 219, 221, 53, 179, 210, 198, 10, 254, 44, 72, 91, 249, 2, 237, 14, 1, 6, 162, 71, 107, 85, 67, 56, 204, 25, 16, 100, 165, 11, 239, 188, 245, 137, 66, 232, 106, 55, 174, 158, 213, 74, 175, 227, 134, 93, 102, 164, 228, 141, 57, 112, 177, 17, 81, 205, 132, 172, 149, 116, 242, 151, 152, 19, 130, 255, 166, 98, 173, 24, 183, 143, 64, 33, 4, 78, 244, 124, 155, 21, 79, 8, 110, 224, 184, 191, 41, 168, 231, 154, 142, 192, 243, 145, 176, 252, 90, 49, 111, 34, 209, 109, 140, 236, 121, 216, 212, 83, 138, 5, 167, 118, 222, 190, 171, 60, 238, 50, 51, 217, 150, 178, 250, 7, 200, 20, 68, 251, 241, 103, 108, 87, 193, 157, 195, 36, 211, 133, 62, 253, 48, 65, 248, 226, 208, 75, 201, 88, 153, 95, 23, 101, 125, 22, 94, 31, 147, 9, 54, 86, 77, 229, 73, 194, 123, 202, 70};
  for (int i = 0; i < SIZE; i++)
    map[i] = array[i];

  // ???????????????? ?? ???????????? ????????????
  /*bool flags[SIZE];
  for (int i = 0; i < SIZE; i++)
    flags[i] = false;
  ofstream fout;
  fout.open("Rotor3.txt");
  fout.setf(ios::dec);
  for (int i = 0; i < SIZE; i++)
  {
    if (!flags[map[i]])
      flags[map[i]] = true;
    else
      printf("Rotor error %d ", map[i]);
    fout << dec << +map[i] << endl;
    //fout << dec << +map[i] << ", ";
  }
  fout.close();*/

  cur_pos = 0;
  rotate_char = 'W';
}

Rotor3::Rotor3(int pos) : Rotor3()
{
  cur_pos = pos;
}
