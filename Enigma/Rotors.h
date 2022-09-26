#ifndef ROTORS_H
#define ROTORS_H

#include <string>

using namespace std;

class Rotor
{
public:
  Rotor() = default;
  Rotor(int pos);
  Rotor(char pos);
  virtual ~Rotor() = 0;

  char getCurChar();
  string getMap();
  char forward(char in, char prev_char = 'A');
  char backward(char in, char next_char = 'A');
  bool rotate();
  void setPos(char pos);

protected:
  int getAlphabetIndex(char c);
  int getMapIndex(char c);

protected:
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int cur_pos = 0;
  char rotate_char = 'Z';
};

class Rotor1 : public Rotor
{
public:
  Rotor1();
  Rotor1(int pos);
  Rotor1(char pos);
};

class Rotor2 : public Rotor
{
public:
  Rotor2();
  Rotor2(int pos);
  Rotor2(char pos);
};

class Rotor3 : public Rotor
{
public:
  Rotor3();
  Rotor3(int pos);
  Rotor3(char pos);
};

#endif // ROTORS_H
