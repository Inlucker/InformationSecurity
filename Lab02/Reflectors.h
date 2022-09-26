#ifndef REFLECTORS_H
#define REFLECTORS_H

#include <string>
#include <iostream>

#include "Rotors.h"

using namespace std;

class Reflector
{
public:
  Reflector() = default;
  virtual ~Reflector() = 0;

  unsigned char reflect(unsigned char in, Rotor *rotor);

protected:
  //string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  //string map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  unsigned char alphabet[SIZE];
  unsigned char map[SIZE];
};

class ReflectorB : public Reflector
{
public:
  ReflectorB();
};

#endif // REFLECTORS_H
