#include<iostream>
#include<string>
#include<vector>
#include<fstream>
/**Testes**/
#include "parser.h"
using namespace std;
int main(int argc,char **argv)
{
    /**Teste do parser**/
//    cout << PARSER::islabel("L1:") << endl;
//    cout << PARSER::islabel("!L1") << endl;
//    cout << PARSER::isdir("CONST") << endl;
//    cout << PARSER::isdir("!CONST") << endl;
//    cout << PARSER::isinst("ADD")  << endl;
//    cout << PARSER::isinst("!ADD") << endl;
//    cout << PARSER::iscomment(";comment") << endl;
//    cout << PARSER::iscomment("!comment") << endl;
    vector<Linha> memoria;
    string nome_base(argv[1]);
    string run_type(argv[2]);
    string nome_arq = nome_base+".asm";
    memoria = PARSER::toMEM(nome_arq);
    //for(unsigned int i=0;i<memoria.size();i++)
    //{
    //cout << memoria[i] << endl;
    //}
    /**Se -p roda EQU**/
    if(run_type==run_type::PRE_PROCESS_EQU)
    {
        PARSER::erros_list.clear();
        nome_arq.clear();
        nome_arq = nome_base+".pre";
        vector<Linha> memoriaEQU = PARSER::pre_proc(memoria);
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

    }
    else
    {
        cout << "Run type nao definido" << endl;
    }
    return 0;
}
//inutil eças funcao


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
