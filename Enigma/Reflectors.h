#ifndef REFLECTORS_H
#define REFLECTORS_H

#include <string>

#include "Rotors.h"

using namespace std;

class Reflector
{
public:
  Reflector() = default;
  virtual ~Reflector() = 0;

  char reflect(char in, char prev_char = 'A');
  char reflect(char in, Rotor *rotor);

protected:
  int getAlphabetIndex(char c);

protected:
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

class ReflectorB : public Reflector
{
public:
  ReflectorB();
};

#endif // REFLECTORS_H
