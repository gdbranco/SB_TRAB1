#include <algorithm>
#include<string>

#include"Rot.h"
Rotulo::Rotulo(string _rot)
{
	setValor(_rot);
}

void Rotulo::validar(string _rot)
{
	size_t found = _rot.find_first_of(":");
	if(found==string::npos)
	{
		throw invalid_argument("Rotulo invalido.");
	}
}
