#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<sstream>
#include<fstream>
#include "OpV.h"
using namespace std;
/*Ignora comentario e ajeita os EQU*/
string primeira_passagi(string arquivao);
void toMEM(string nome, string &memoria);

int main()
{
	OpV validos;
	validos.showValidos();
	cout<<endl;
	//string memoria;
	//toMEM("teste.asm", memoria);
	//	cout<<memoria<<endl;
	//primeira_passagi(memoria);
	return 0;
}

void toMEM(string nome, string &memoria)
{
	size_t tam;
	fstream sc;
	sc.open(nome.c_str());
	sc.seekg(0,sc.end);
	tam = sc.tellg();
	sc.seekg(0,sc.beg);
	char *buffer = new char[tam];
	sc.read(buffer,tam-1);
	memoria.assign(buffer);
	sc.close();
	return;
}

string primeira_passagi(fstream memoria)
{
	vector<string> tokens;
	string s;
	getline(memoria, s);
	cout << s << endl;	
	return "oi";
}

/*linha pre_proc(string memoria)
{

	stringstream s_str(memoria);
	char * pch;
	vector<linha> linhas;
	linha _aux;
	int _n_linha=0;
	getline(s_str,s);
	do
	{
		_n_linha++;
		_aux.n_linha = _n_linha;
		pch = strtok((char*)s.c_str(),"\t ");
		while(pch!=NULL)
		{
			cout << pch << endl;
			pch = strtok(NULL,"\t ");
			_aux.tokens.push_back(new string(pch));
		}
	linhas.push_back(
	}while(getline(s_str, s));
	return "oi";
}*/
