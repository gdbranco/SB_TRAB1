#ifndef OP_H
#define OP_H
#include "Basicos.h"
#include "OpV.h"
#include <vector>
class Operador:public TipoBasico
{
private:
	void validar(string);
public:
	Operador(){};
	Operador(string);
}
#endif
