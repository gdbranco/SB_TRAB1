#ifndef OP_H
#define OP_H
#include "Basico.h"
#include <vector>
#include <fstream>
#define operadoresV "operadoresValidos.txt"
class Operador:public TipoBasico
{
private:
	void validar(string);
	static vector<string> Validos;
public:
	Operador(){setValidos();};
	Operador(string);
	void setValidos();
	void showValidos();
	int pesquisar(string);
};
#endif
