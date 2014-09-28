#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<sstream>
#include<fstream>
/**Testes**/
#include "Line.h"
#include "Macro.h"
using namespace std;
/*Ignora comentario e ajeita os EQU*/
void toMEM(string nome, string &memoria);

int main()
{
    vector<Operando> to_op;
    to_op.push_back(Operando("FACT"));
    to_op.push_back(Operando("ONE"));
    Line line(Rotulo("_L1:"),Operador("ADD"),to_op,0);
    cout <<line;
    /**Teste macro*/
//    Macro macro("TROCA AQUI","add 1 2\nsub 3 2\n");
//    cout << macro;
    /**Teste das inst e dir validas*/
	//Operador teste;
	//teste.showValidos();
	//cout<<endl;
    /**Primeiro teste de pre proc !funciona*/
	//string memoria;
	//toMEM("teste.asm", memoria);
	//	cout<<memoria<<endl;
	//primeira_passagi(memoria);
	return 0;
}
/**inutil eças funcao*/
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
