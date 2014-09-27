#include <algorithm>
#include<string>

#include"Rot.h"
Rot::Rot(string _rot)
{
	setValor(_rot);
}

void Rot::validar(string _rot)
{
	size_t found = email.find_first_of(":");
	if(found==string::npos)
	{
		throw invalid_argument("Rotulo invalido.");
	}
}
