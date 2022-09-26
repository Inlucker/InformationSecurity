#include "Enigma.h"

Enigma::Enigma() :
  r1(new Rotor1()),
  r2(new Rotor2()),
  r3(new Rotor3()),
  ref(new ReflectorB())
{
  for (int i = 0; i < 3; i ++)
    start_pos[i] = 0;
}

Enigma::Enigma(unsigned char pos1, unsigned char pos2, unsigned char pos3) :
  r1(new Rotor1(pos1)),
  r2(new Rotor2(pos2)),
  r3(new Rotor3(pos3)),
  ref(new ReflectorB())
{
  setup(pos1, pos2, pos3);
}

Enigma::~Enigma()
{
  delete r1;
  delete r2;
  delete r3;
  delete ref;
}

void Enigma::reset()
{
  r1->setPos(start_pos[0]);
  r2->setPos(start_pos[1]);
  r3->setPos(start_pos[2]);
}

void Enigma::setup(unsigned char pos1, unsigned char pos2, unsigned char pos3)
{
  start_pos[0] = pos1;
  start_pos[1] = pos2;
  start_pos[2] = pos3;
}

unsigned char *Enigma::encipher(size_t size, unsigned char *input)
{
  unsigned char* output = new unsigned char[size];
  for (size_t i = 0; i < size; i++)
    output[i] = 0;

  for (size_t i = 0; i < size; i++)
  {
    if (r1->rotate())
      if (r2->rotate())
        r3->rotate();

    unsigned char tmp = input[i];

    tmp = r1->forward(tmp);
    tmp = r2->forward(tmp, r1->getCurChar());
    tmp = r3->forward(tmp, r2->getCurChar());

    tmp = ref->reflect(tmp, r3);

    tmp = r3->backward(tmp, r2->getCurChar());
    tmp = r2->backward(tmp, r1->getCurChar());
    tmp = r1->backward(tmp);

    output[i] = tmp;
  }
  reset();
  return output;
}
