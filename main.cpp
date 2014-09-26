#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;
/*Ignora comentario e ajeita os EQU*/
string primeira_passagi(string arquivao);
void toMEM(string nome, string &memoria);

int main()
{
	string memoria;
	toMEM("teste.asm", memoria);
	//	cout<<memoria<<endl;
	primeira_passagi(memoria);
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

string primeira_passagi(string memoria)
{
	stringstream s_str(memoria);
	char * pch;
	string s;
	getline(s_str,s);
	do
	{
		pch = strtok((char*)s.c_str(),"\t ");
		while(pch!=NULL)
		{
			cout << pch << endl;
			pch = strtok(NULL,"\t ");
		}
	}while(getline(s_str, s));
	return "oi";
}
