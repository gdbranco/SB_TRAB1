#include<iostream>
#include<string>
#include<vector>
#include<fstream>
/**Testes**/
#include "parser.h"
using namespace std;
int main(int argc,char **argv)
{
    code_t memoria;
    string nome_base(argv[1]);
    string run_type(argv[2]);
    string nome_arq = nome_base+".asm";
    memoria = PARSER::toMEM(nome_arq);
    /**Se -p roda EQU**/
    if(run_type==run_type::PRE_PROCESS_EQU)
    {
        PARSER::erros_list.clear();
        nome_arq.clear();
        nome_arq = nome_base+".pre";
        code_t memoriaEQU = PARSER::run_preproc(memoria);
        /**Se nao houver erros e a memoria nao for vazia abre o arquivo .pre**/
        if(!memoriaEQU.empty() && PARSER::erros_list.empty())
        {
            ofstream myarq;
            myarq.open(nome_arq.c_str());
            for(unsigned int i=0; i<memoriaEQU.size(); i++)
            {
                //cout << memoriaEQU[i].nlinha << ' ';
                myarq << memoriaEQU[i];
                //cout << memoriaEQU[i];
                if(i!=memoriaEQU.size()-1)
                {
                    myarq << endl;
                    //cout << endl;
                }
            }
            myarq.close();
        }
        /**Se houver erros nao abre o arquivo e mostra os erros na tela**/
        else
        {
            cout << "---ERROS---" << endl;
            for(unsigned int i=0; i<PARSER::erros_list.size(); i++)
            {
                cout << PARSER::erros_list[i] << endl;
            }
        }
    }
    else if(run_type==run_type::PRE_PROCESS_MACRO)
    {

    }
    else if(run_type==run_type::COMPILE)
    {
        code_t memoriaMNT = PARSER::run_montador(memoria);
    }
    else
    {
        cout << "Run type nao definido" << endl;
    }
    return 0;
}
