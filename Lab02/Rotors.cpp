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
  random_shuffle(&map[0], &map[SIZE]);

  // Проверка и запись ротора
  /*bool flags[SIZE];
  for (int i = 0; i < SIZE; i++)
    flags[i] = false;
  ofstream fout;
  fout.open("Rotor1.txt"); // связываем объект с файлом
  fout.setf(ios::dec);
  for (int i = 0; i < SIZE; i++)
  {
    if (!flags[map[i]])
      flags[map[i]] = true;
    else
      printf("Rotor error %d ", map[i]);
    fout << dec << +map[i] << endl;
  }
  fout.close(); // закрываем файл*/

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
  random_shuffle(&map[0], &map[SIZE]);

  // Проверка и запись ротора
  /*bool flags[SIZE];
  for (int i = 0; i < SIZE; i++)
    flags[i] = false;
  ofstream fout;
  fout.open("Rotor2.txt"); // связываем объект с файлом
  fout.setf(ios::dec);
  for (int i = 0; i < SIZE; i++)
  {
    if (!flags[map[i]])
      flags[map[i]] = true;
    else
      printf("Rotor error %d ", map[i]);
    fout << dec << +map[i] << endl;
  }
  fout.close(); // закрываем файл*/

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
  random_shuffle(&map[0], &map[SIZE]);

  // Проверка и запись ротора
  /*bool flags[SIZE];
  for (int i = 0; i < SIZE; i++)
    flags[i] = false;
  ofstream fout;
  fout.open("Rotor3.txt"); // связываем объект с файлом
  fout.setf(ios::dec);
  for (int i = 0; i < SIZE; i++)
  {
    if (!flags[map[i]])
      flags[map[i]] = true;
    else
      printf("Rotor error %d ", map[i]);
    fout << dec << +map[i] << endl;
  }
  fout.close(); // закрываем файл*/

  cur_pos = 0;
  rotate_char = 'W';
}

Rotor3::Rotor3(int pos) : Rotor3()
{
  cur_pos = pos;
}
