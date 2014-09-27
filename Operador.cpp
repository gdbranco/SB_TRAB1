#include<algorithm>
#include<string>

#include"Operador.h"

vector<string> Operador::Validos;
void Operador::setValidos()
{
	fstream outarq;
	outarq.open(operadoresV);
	string s;
	while(getline(outarq,s))
	{
		if(s.compare(""))
			Validos.push_back(s);
	}
	outarq.close();
}

int Operador::pesquisar(string pesquisa)
{
	for(unsigned int i=0;i<Validos.size();i++)
	{
		if(!pesquisa.compare(Validos.at(i)))
		{
			return 1;
		}
	}
	return 0;
}

void Operador::showValidos()
{
	for(unsigned int i=0;i<Validos.size();i++)
	{
		cout<< Validos.at(i) <<endl;
	}
}

Operador::Operador(string _op)
{
	setValor(_op);
}

void Operador::validar(string _op)
{
    throw invalid_argument("Operador/Diretiva invalidos.");
}
