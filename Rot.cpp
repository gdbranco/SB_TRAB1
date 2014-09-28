#include"Rot.h"
Rotulo::Rotulo(string _rot)
{
	setValor(_rot);
}

void Rotulo::validar(string _rot)
{
	size_t found = _rot.find_first_of(":");
	if(found!=string::npos)
	{
	    if(_rot[found+1]!='\0')
            throw invalid_argument("Rotulo invalido.");
	}
	else
        throw invalid_argument("Rotulo invalido.");
}

ostream& operator<<(ostream& os, const Rotulo& it)
{
    os << it.getValor();
    return os;
}
