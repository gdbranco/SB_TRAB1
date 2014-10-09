#ifndef DEFINE_H
#define DEFINE_H
#include <utility>
#include <string>
using namespace std;
namespace sections
{
    extern string S;
    extern string TEXT;
    extern string DATA;
}
namespace instructions
{
    extern pair<string,int> ADD;
    extern pair<string,int> SUB;
    extern pair<string,int> MULT;
    extern pair<string,int> DIV;
    extern pair<string,int> JMP;
    extern pair<string,int> JMPN;
    extern pair<string,int> JMPP;
    extern pair<string,int> JMPZ;
    extern pair<string,int> COPY;
    extern pair<string,int> LOAD;
    extern pair<string,int> STORE;
    extern pair<string,int> INPUT;
    extern pair<string,int> OUTPUT;
    extern pair<string,int> STOP;
    extern int tamanhoGeral;
    extern int tamanhoCOPY;
    extern int tamanhoSTOP;
}
namespace diretivas
{
    extern string TEXT;
    extern string DATA;
    extern string SECTION;
    extern string SPACE;
    extern string CONST;
    extern string EQU;
    extern string IF;
    extern string MACRO;
    extern string END;
}
#endif // DEFINE_H
