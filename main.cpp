#include<iostream>
#include<string>
#include<vector>
#include<fstream>
/**Testes**/
#include "parser.h"
using namespace std;

void handle_pass(std::string nome_arq, code_t &memoria, const string run_type, bool log);

int main(int argc,char **argv)
{
	if(argc<3)
	{
		return -1;
	}
	code_t memoria;
	string nome_base(argv[1]);
	string run_type(argv[2]);
	string nome_arq = nome_base+".asm";
	memoria = PARSER::toMEM(nome_arq);
	//for(unsigned int i=0;i<memoria.size();i++)
	//{
		//cout << memoria[i] << endl;
	//}
	//cin.get();
	/**Roda as passagens apropriadas dependendo da flag passada
	 * -p roda só pré-processamento, -m roda macros também, -o roda tudo**/
	if(run_type==run_type::PRE_PROCESS_EQU)
	{
		handle_pass(string(nome_base + ".pre"), memoria, run_type::PRE_PROCESS_EQU, true);
	}
	else if(run_type==run_type::PRE_PROCESS_MACRO)
	{
		handle_pass(string(nome_base + ".pre"), memoria, run_type::PRE_PROCESS_EQU, false);
		handle_pass(string(nome_base + ".mcr"), memoria, run_type::PRE_PROCESS_MACRO, true);
	}
	else if(run_type==run_type::COMPILE)
	{
		handle_pass(string(nome_base + ".pre"), memoria, run_type::PRE_PROCESS_EQU, false);
		handle_pass(string(nome_base + ".mcr"), memoria, run_type::PRE_PROCESS_MACRO, false);
		handle_pass(string(nome_base + ".o"), memoria, run_type::COMPILE, true);
	}
	else
	{
		cout << "Run type nao definido" << endl;
	}
	return 0;
}

void handle_pass(std::string nome_arq, code_t &memoria, const string run_type, bool log) {
	code_t memoriaLOCAL;

	/*Roda a passagem correta e seta a memória*/
	if (run_type==run_type::PRE_PROCESS_EQU) {
		memoriaLOCAL = PARSER::run_preproc(memoria);
	} else if (run_type==run_type::PRE_PROCESS_MACRO) {
		memoriaLOCAL = PARSER::run_macros(memoria);
	} else {
		memoriaLOCAL = PARSER::run_montador(memoria);
	}


	ofstream myarq;
	unsigned found = nome_arq.find_last_of("/\\");
	if(found)
	{
		nome_arq = nome_arq.substr(found+1);
	}

	/*Loga os erros e imprime o arquivo*/
	if (log) {
		myarq.open(nome_arq.c_str());

		if(!memoriaLOCAL.empty() && PARSER::erros_list.empty()) {
			for(unsigned int i=0; i<memoriaLOCAL.size(); i++)
			{
				//cout << memoriaEQU[i].nlinha << ' ';
				//cout << memoriaMACRO[i];
				myarq << memoriaLOCAL[i];
				if(i!=memoriaLOCAL.size()-1)
				{
					myarq << endl;
				}

			}

		}
		else
		{
			cout << "---ERROS---" << endl;
			for(unsigned int i=0; i<PARSER::erros_list.size(); i++)
			{
				cout << PARSER::erros_list[i] << endl;
			}
		}

		myarq.close();
	}

	/*Seta a memoria passada para a memória local*/
	memoria = memoriaLOCAL;
}
