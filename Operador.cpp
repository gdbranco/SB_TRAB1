#include<algorithm>
#include<string>

#include"Operador.h"
Operador::Operador(string _op)
{
	setValor(_op);
}

void Operador::validar(string _op)
{
	if(!(validados.pesquisar(_op))
	{
		throw invalid_argument("Operador/Diretiva invalidos.");
	}	
}
