#ifndef ENIGMA_H
#define ENIGMA_H

#include "Rotors.h"
#include "Reflectors.h"

class Enigma
{
public:
  Enigma();
  Enigma(unsigned char pos1, unsigned char pos2, unsigned char pos3);
  ~Enigma();

  void reset();
  void setup(unsigned char pos1, unsigned char pos2, unsigned char pos3);
  unsigned char *encipher(size_t size, unsigned char *input);

private:
  Rotor *r1;
  Rotor *r2;
  Rotor *r3;
  Reflector *ref;
  unsigned char start_pos[3];
};

#endif // ENIGMA_H
