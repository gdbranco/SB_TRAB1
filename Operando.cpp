#include "Operando.h"
Operando::Operando(string _nome)
{
	setValor(_nome);
}

void Operando::validar(string _operando)
{

}

ostream& operator<<(ostream& os, const Operando& it)
{
    os << it.getValor();
    return os;
}
