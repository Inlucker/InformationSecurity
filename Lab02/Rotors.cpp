#include "Rotors.h"

// AbstractRotor
Rotor::Rotor(int pos) : cur_pos(pos) {}

Rotor::Rotor(char pos)
{
  cur_pos = getAlphabetIndex(pos);
}

Rotor::~Rotor() {}

int Rotor::getMapIndex(char c)
{
  int index = map.find(c);
  return index;
}

int Rotor::getAlphabetIndex(char c)
{
  if (c > 90)
    c -= 32;
  int index = c - 'A';
  return index;
}

char Rotor::getCurChar()
{
  return alphabet[cur_pos];
}

string Rotor::getMap()
{
  return map;
}

char Rotor::forward(char in, char prev_char)
{
  int index = (getAlphabetIndex(in) + (cur_pos - getAlphabetIndex(prev_char))) % 26;
  if (index < 0)
    index += 26;
  char out = map[index];
  return out;
}

char Rotor::backward(char in, char next_char)
{
  in = alphabet[getMapIndex(in)];
  int index = (getAlphabetIndex(in) - (cur_pos - getAlphabetIndex(next_char))) % 26;
  if (index < 0)
    index += 26;
  char out = alphabet[index];
  return out;
}

bool Rotor::rotate()
{
  cur_pos = (cur_pos + 1) % 26;
  bool flag = alphabet[cur_pos] == rotate_char;
  return flag;
}

// Rotor1
Rotor1::Rotor1()
{
  map = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
  cur_pos = 0;
  rotate_char = 'R';
}

Rotor1::Rotor1(int pos) : Rotor1()
{
  cur_pos = pos;
}

Rotor1::Rotor1(char pos) : Rotor1()
{
  cur_pos = getAlphabetIndex(pos);
}

// Rotor2
Rotor2::Rotor2()
{
  map = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
  cur_pos = 0;
  rotate_char = 'F';
}

Rotor2::Rotor2(int pos) : Rotor2()
{
  cur_pos = pos;
}

Rotor2::Rotor2(char pos) : Rotor2()
{
  cur_pos = getAlphabetIndex(pos);
}

// Rotor3
Rotor3::Rotor3()
{
  map = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
  cur_pos = 0;
  rotate_char = 'W';
}

Rotor3::Rotor3(int pos) : Rotor3()
{
  cur_pos = pos;
}

Rotor3::Rotor3(char pos) : Rotor3()
{
  cur_pos = getAlphabetIndex(pos);
}
