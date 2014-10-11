#ifndef DEFINE_H
#define DEFINE_H
#include <utility>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef struct _linha
{
    int nlinha;
    vector<string> tokens;
    _linha() {}
    _linha(int _nlinha, vector<string> _tokens)
    {
        this-> nlinha = _nlinha;
        this-> tokens = _tokens;
    }
    _linha(int error_type)
    {

    }
    friend ostream& operator<<(ostream& os, const _linha& it)
    {
        os << it.nlinha << ' ';
        for(unsigned int i =0; i<it.tokens.size(); i++)
        {
            cout << it.tokens[i] << ' ';
        }
        return os;
    }
} Linha;
typedef struct _define
{
    int value;
    string label;
    _define(){}
    _define(string _label,int _value)
    {
        this->label = _label;
        this->value = _value;
    }
    friend bool operator==(_define& define1, _define& define2)
    {
        return (define1.label == define2.label);
    }
    friend ostream& operator<<(ostream& os, const _define& it)
    {
        os << it.label << ' ' << it.value;
        return os;
    }
}Define;
typedef struct _erro
{
    int nlinha;
    string type;
    string reason;
    _erro(){}
    _erro(int _nlinha,string _type,string _reason)
    {
        this->nlinha = _nlinha;
        this->type = _type;
        this->reason = _reason;
    }
    friend ostream& operator<<(ostream& os,const _erro& it)
    {
        os << "erro : linha "<<it.nlinha << ", devido a " << it.type << ", pois " << it.reason;
        return os;
    }
}Erro;
namespace erros
{
    extern string SINTATICO;
    extern string SEMANTICO;
    extern string LEXICO;
    extern string label_redefinida;
    extern string label_dupla;
    extern string EQU_nlabeled;
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
