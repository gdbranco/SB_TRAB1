#ifndef ROT_H
#define ROT_H

#include <string>

using namespace std;

class Rotulo:public TipoBasico
{
private:
	void validar(string);
public:
	Rotulo(){};
	Rotulo(string);
}
