#ifndef ROT_H
#define ROT_H

#include <string>
#include "Basico.h"
using namespace std;

class Rotulo:public TipoBasico
{
private:
	void validar(string _label);
public:
	Rotulo(){};
	Rotulo(string);
	friend ostream& operator<<(ostream& os, const Rotulo& it);
};
#endif
