#include "defines.h"
namespace erros
{
    string SINTATICO = "ERRO SINTATICO";
    string SEMANTICO = "ERRO SEMANTICO";
    string LEXICO    = "ERRO LEXICO";
    string label_redefinida = "Redefinicao de label";
    string label_dupla      = "Duas labels na mesma linha";
    string EQU_nlabeled     = "EQU sem label";
    string EQU_ndefinida  = "EQU nao definido";
    string MACRO_no_label  = "Macro não pode ser definida sem label";
    string MACRO_label_no_delimiter  = "Label da macro precisa terminar em ':'";
    string MACRO_endless  = "Macro sem delimitação final";
}
namespace instructions
{
    pair<string,int> ADD    = make_pair("ADD",1);
    pair<string,int> SUB    = make_pair("SUB",2);
    pair<string,int> MULT   = make_pair("MULT",3);
    pair<string,int> DIV    = make_pair("DIV",4);
    pair<string,int> JMP    = make_pair("JMP",5);
    pair<string,int> JMPN   = make_pair("JMPN",6);
    pair<string,int> JMPP   = make_pair("JMPP",7);
    pair<string,int> JMPZ   = make_pair("JUMPZ",8);
    pair<string,int> COPY   = make_pair("COPY",9);
    pair<string,int> LOAD   = make_pair("LOAD",10);
    pair<string,int> STORE  = make_pair("STORE",11);
    pair<string,int> INPUT  = make_pair("INPUT",12);
    pair<string,int> OUTPUT = make_pair("OUTPUT",13);
    pair<string,int> STOP   = make_pair("STOP",14);
    int tamanhoGeral = 2;
    int tamanhoCOPY  = 3;
    int tamanhoSTOP  = 1;
}
namespace diretivas
{
    string TEXT    = "TEXT";
    string DATA    = "DATA";
    string SECTION = "SECTION";
    string SPACE   = "SPACE";
    string CONST   = "CONST";
    string EQU     = "EQU";
    string IF      = "IF";
    string MACRO   = "MACRO";
    string END     = "END";
}
