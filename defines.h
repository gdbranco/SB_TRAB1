#ifndef DEFINE_H
#define DEFINE_H
#include <utility>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef struct _smb
{
    string simb;
    int value;
    bool def;
    vector<int> lista_end;
    _smb(){}
    _smb(const string _simb, const int _value,const bool _def,const vector<int> _lista_end):simb(_simb),value(_value),def(_def),lista_end(_lista_end) { }
    friend ostream& operator<<(ostream& os,const _smb& it)
    {
        os << it.simb << ' ';
        os << it.value << ' ';
        os << it.def   << ' ';
        for(unsigned int i=0;i<it.lista_end.size();i++)
        {
            os << it.lista_end[i];
            if(i!=it.lista_end.size())
            {
                os << ' ';
            }
        }
        return os;
    }
}smb_t;
typedef vector<smb_t> tsmb_t;
typedef struct _linha
{
    int nlinha;
    vector<string> tokens;
    _linha() {}
    _linha(int _nlinha, vector<string> _tokens):nlinha(_nlinha),tokens(_tokens) { }
    friend ostream& operator<<(ostream& os, const _linha& it)
    {
        for(unsigned int i =0; i<it.tokens.size(); i++)
        {
            os << it.tokens[i];
            if(i!=it.tokens.size()-1)
            {
                os << ' ';
            }
        }
        return os;
    }
} linha_t;
typedef vector<linha_t> code_t;
typedef struct _define
{
    string label;
    int value;
    _define(){}
    _define(string _label,int _value):label(_label),value(_value) { }
    friend bool operator==(_define& define1, _define& define2)
    {
        return (define1.label == define2.label);
    }
    friend ostream& operator<<(ostream& os, const _define& it)
    {
        os << it.label << ' ' << it.value;
        return os;
    }
}define_t;
typedef struct _erro
{
    int nlinha;
    string type;
    string reason;
    _erro(){}
    _erro(int _nlinha,string _type,string _reason):nlinha(_nlinha),type(_type),reason(_reason){ }
    friend ostream& operator<<(ostream& os,const _erro& it)
    {
        os << "erro : linha "<<it.nlinha << ", devido a " << it.type << ", pois " << it.reason;
        return os;
    }
}erro_t;
namespace run_type
{
    extern string PRE_PROCESS_EQU;
    extern string PRE_PROCESS_MACRO;
    extern string COMPILE;
}
namespace erros
{
    extern string SINTATICO;
    extern string SEMANTICO;
    extern string LEXICO;
    extern string label_redefinida;
    extern string label_dupla;
    extern string EQU_nlabeled;
    extern string EQU_ndefinida;
}
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
