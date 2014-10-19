#include<iostream>
#include<string>
#include<vector>
#include<fstream>
/**Testes**/
#include "parser.h"
using namespace std;

/*	*Função única para realizar cada passada. Definida pela string "run_type". Loga os erros se "lol" for true.
	*Recebe uma memória encapsulada em um virtual_code_wrapper. No input, code_wrapper sempre vai ser do tipo text_code_wrapper.
	*Na passagem única retorna um object_code (vector<int>) encapsulado em um obj_code_wrapper.*/
virtual_code_wrapper* handle_pass(std::string nome_arq, virtual_code_wrapper* code_wrapper, const string run_type, bool log);

int main(int argc,char **argv)
{
    if(argc<3)
    {
        return -1;
    }
    code_t memoria;
    string run_type(argv[1]);
    string nome_base(argv[2]);
    string nome_arq = nome_base+".asm";
    memoria = PARSER::toMEM(nome_arq);

	/*virtual_code_wrapper serve como abstração para os tipos de código diferentes (vector<linha> e vector<int>)*/
	virtual_code_wrapper* mem_wrapper;


    /**Roda as passagens apropriadas dependendo da flag passada
     * -p roda só pré-processamento, -m roda macros também, -o roda tudo**/
    if(run_type==run_type::PRE_PROCESS_EQU)
    {
		mem_wrapper = new text_code_wrapper(memoria); 
        handle_pass(string(nome_base + ".pre"), mem_wrapper, run_type::PRE_PROCESS_EQU, true);
    }
    else if(run_type==run_type::PRE_PROCESS_MACRO)
    {
		mem_wrapper = new text_code_wrapper(memoria); 
        handle_pass(string(nome_base + ".pre"), mem_wrapper, run_type::PRE_PROCESS_EQU, false);
        handle_pass(string(nome_base + ".mcr"), mem_wrapper, run_type::PRE_PROCESS_MACRO, true);
    }
    else if(run_type==run_type::COMPILE)
    {
		mem_wrapper = new text_code_wrapper(memoria); 
        handle_pass(string(nome_base + ".pre"), mem_wrapper, run_type::PRE_PROCESS_EQU, false);
        handle_pass(string(nome_base + ".mcr"), mem_wrapper, run_type::PRE_PROCESS_MACRO, false);
        handle_pass(string(nome_base + ".o"), mem_wrapper, run_type::COMPILE, true);
    }
    else
    {
        cout << "Run type nao definido" << endl;
    }
    return 0;
}

virtual_code_wrapper* handle_pass(std::string nome_arq, virtual_code_wrapper* code_wrapper, const string run_type, bool log)
{
    code_t memoriaLOCAL;
	vector<int> obj_codeLOCAL;

    /*Roda a passagem correta e seta a memória*/
    if (run_type==run_type::PRE_PROCESS_EQU)
    {
		/*Roda o pré-processamento para o código dentro de code_wrapper (vector<linha>)*/
        memoriaLOCAL = PARSER::run_preproc(   (  (text_code_wrapper*) code_wrapper)->code_impl   );
		code_wrapper = new text_code_wrapper(memoriaLOCAL); 
    }
    else if (run_type==run_type::PRE_PROCESS_MACRO)
    {
		/*Roda a passagem de macros para o código dentro de code_wrapper (vector<linha>)*/
        memoriaLOCAL = PARSER::run_macros(   (  (text_code_wrapper*) code_wrapper)->code_impl   );
		code_wrapper = new text_code_wrapper(memoriaLOCAL); 
    }
    else
    {
		/* Roda a passagem única para o código dentro de code_wrapper (vector<linha>)
		 * Retorna um obj_code (vector<int>)*/
        obj_codeLOCAL = PARSER::run_montador(   (  (text_code_wrapper*) code_wrapper)->code_impl  );
		code_wrapper = new obj_code_wrapper(obj_codeLOCAL); 
    }


    ofstream myarq;
    unsigned found = nome_arq.find_last_of("/\\");
    if(found)
    {
        nome_arq = nome_arq.substr(found+1);
    }

    /*Loga os erros e imprime o arquivo*/
    if (log)
    {
        myarq.open(nome_arq.c_str());

        if(PARSER::erros_list.empty())
        {
			if (run_type == run_type::COMPILE ) {
				if (!obj_codeLOCAL.empty()) {
					for(unsigned int i=0; i<obj_codeLOCAL.size(); i++)
					{
						myarq << obj_codeLOCAL[i];
						if(i!=obj_codeLOCAL.size()-1)
						{
							myarq << " ";
						}
					}
				}
			} else {
				if (!memoriaLOCAL.empty()) {
					for(unsigned int i=0; i<memoriaLOCAL.size(); i++)
					{
						//cout << memoriaLOCAL[i] << endl;
						myarq << memoriaLOCAL[i];
						if(i!=memoriaLOCAL.size()-1)
						{
							myarq << endl;
						}

					}
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

}
