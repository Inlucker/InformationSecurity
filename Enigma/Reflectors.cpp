#include "Reflectors.h"

Reflector::~Reflector() {}

int Reflector::getAlphabetIndex(char c)
{
  if (c > 90)
    c -= 32;
  int index = c - 'A';
  return index;
}

char Reflector::reflect(char in, char prev_char)
{
  int index = getAlphabetIndex(in) - getAlphabetIndex(prev_char);
  if (index < 0)
    index += 26;
  else
    index %= 26;
  char out = map[index];

  index = (getAlphabetIndex(out) + getAlphabetIndex(prev_char)) % 26;
  out = alphabet[index];

  return out;
}

char Reflector::reflect(char in, Rotor *rotor)
{
  int prev_index = getAlphabetIndex(rotor->getCurChar());
  int index = getAlphabetIndex(in) - prev_index;
  if (index < 0)
    index += 26;
  else
    index %= 26;
  char tmp = map[index];

  index = (getAlphabetIndex(tmp) + prev_index) % 26;
  //tmp = alphabet[index];
  char out = alphabet[index];

  //index = rotor->getMapIndex(tmp);
  //char out = alphabet[index];

  return out;
}

//ReflectorB
ReflectorB::ReflectorB()
{
  map = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
}
