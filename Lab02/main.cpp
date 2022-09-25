#include <iostream>

#include "Rotors.h"
#include "Reflectors.h"

using namespace std;

int main()
{
  Rotor *r1 = new Rotor1('Q');
  Rotor *r2 = new Rotor2('U');
  Rotor *r3 = new Rotor3('C');
  Reflector *ref = new ReflectorB();

  string input = "TheXquickXbrownXfoxXjumpsXoverXtheXlazyXdog";
  //input = "ZFWOERYTVJAYVZKKJVZVUSYWEMXBMHORBITYZJPZVMF";
  string output = "";

  for (size_t i = 0; i < input.size(); i++)
  {
    if (r1->rotate())
      if (r2->rotate())
        r3->rotate();

    char tmp = input[i];

    tmp = r1->forward(tmp);
    tmp = r2->forward(tmp, r1->getCurChar());
    tmp = r3->forward(tmp, r2->getCurChar());

    tmp = ref->reflect(tmp, r3);

    tmp = r3->backward(tmp, r2->getCurChar());
    tmp = r2->backward(tmp, r1->getCurChar());
    tmp = r1->backward(tmp);

    output += tmp;
  }

  cout << input << endl;
  cout << output << endl;

  delete r1;
  delete r2;
  delete r3;
  delete ref;

  return 0;
}
