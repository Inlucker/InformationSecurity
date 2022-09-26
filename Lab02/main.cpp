#include <iostream>
#include <random>

#include "Enigma.h"

using namespace std;

int generateReflector(unsigned char *map, int size)
{
  bool flags[size];

  for (int i = 0; i < size; i++)
    flags[i] = false;

  for (int i = 0; i < size; i++)
  {
    if (!flags[i])
    {
      unsigned char new_value = rand() % size;
      while (flags[new_value])
        new_value = rand() % size;

      map[i] = new_value;
      map[new_value] = i;
      flags[i] = true;
      flags[new_value] = true;
    }
  }

  return size;
}

int main()
{
  string str = "The quick brown fox jumps over the lazy dog";
  size_t msg_size = str.size();
  unsigned char* input = new unsigned char[msg_size];
  for (size_t i = 0; i < msg_size; i++)
    input[i] = str[i];

  cout << "     Plain text: ";
  for (size_t i = 0; i < msg_size; i++)
    cout << input[i];
  cout << endl;

  /*unsigned char* output = new unsigned char[msg_size];
  for (size_t i = 0; i < msg_size; i++)
    output[i] = 0;

  Rotor *r1 = new Rotor1('Q');
  Rotor *r2 = new Rotor2('U');
  Rotor *r3 = new Rotor3('C');
  Reflector *ref = new ReflectorB();

  for (size_t i = 0; i < msg_size; i++)
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

  cout << "     Plain text: ";
  for (size_t i = 0; i < msg_size; i++)
    cout << input[i];
  cout << endl;

  cout << "    Cipher text: ";
  for (size_t i = 0; i < msg_size; i++)
    cout << output[i];
  cout << endl;

  //input = output;
  for (size_t i = 0; i < msg_size; i++)
    input[i] = output[i];
  //output = "";
  for (size_t i = 0; i < msg_size; i++)
    output[i] = 0;

  r1->setPos('Q');
  r2->setPos('U');
  r3->setPos('C');

  for (size_t i = 0; i < msg_size; i++)
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

  cout << "Enciphered text: ";
  for (size_t i = 0; i < msg_size; i++)
    cout << output[i];
  cout << endl;

  delete r1;
  delete r2;
  delete r3;
  delete ref;*/

  Enigma *enigma = new Enigma('Q', 'U', 'C');
  unsigned char* output = nullptr;

  output = enigma->encipher(msg_size, input);

  cout << "    Cipher text: ";
  for (size_t i = 0; i < msg_size; i++)
    cout << output[i];
  cout << endl;

  for (size_t i = 0; i < msg_size; i++)
    input[i] = output[i];
  for (size_t i = 0; i < msg_size; i++)
    output[i] = 0;

  output = enigma->encipher(msg_size, input);

  cout << "Deciphered text: ";
  for (size_t i = 0; i < msg_size; i++)
    cout << output[i];
  cout << endl;

  delete[] input;
  delete[] output;

  if (enigma->encipher("text.txt", "cipher_text.txt"))
    cout << "File text.txt encipered in cipher_text.txt" << endl;
  else
    cout << "Couldn't encipher file text.txt" << endl;
  if (enigma->encipher("cipher_text.txt", "deciphered_text.txt"))
    cout << "File cipher_text.txt encipered in deciphered_text.txt" << endl;
  else
    cout << "Couldn't encipher file cipher_text.txt" << endl;

  //Генерация рефлектора
  /*int size = SIZE;
  unsigned char* map = new unsigned char[size];
  generateReflector(map, size);

  //for (int i = 0; i < SIZE; i++)
    //printf("%d, ", map[i]);
    //cout << map[i] << " ";

  delete[] map;*/

  return 0;
}
