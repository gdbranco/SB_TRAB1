#include "OpV.h"
vector<string> OpV::Validos;
void OpV::setValidos()
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

int OpV::pesquisar(string pesquisa)
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

void OpV::showValidos()
{
	for(unsigned int i=0;i<Validos.size();i++)
	{
		cout<< Validos.at(i) <<endl;
	}
}
