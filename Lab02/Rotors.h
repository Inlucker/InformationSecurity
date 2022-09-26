#ifndef ROTORS_H
#define ROTORS_H

#include <string>
#include <algorithm>

#define SIZE 256

using namespace std;

class Rotor
{
public:
  Rotor();
  virtual ~Rotor() = 0;

  unsigned char getCurChar();
  unsigned char forward(unsigned char in, unsigned char prev_char = 0);
  unsigned char backward(unsigned char in, unsigned char next_char = 0);
  bool rotate();
  void setPos(int pos);

protected:
  int getMapIndex(unsigned char c);

protected:
  //string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  //string map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unsigned char alphabet[SIZE];
  unsigned char map[SIZE];
  unsigned char cur_pos = 0;
  unsigned char rotate_char = SIZE - 1;
};

class Rotor1 : public Rotor
{
public:
  Rotor1();
  Rotor1(int pos);
};

class Rotor2 : public Rotor
{
public:
  Rotor2();
  Rotor2(int pos);
};

class Rotor3 : public Rotor
{
public:
  Rotor3();
  Rotor3(int pos);
};

#endif // ROTORS_H
