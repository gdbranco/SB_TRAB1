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
    bool is_const;
    vector<int> lista_end;
    _smb() {}
    _smb(const string _simb, const int _value,const bool _def,const vector<int> _lista_end):
        simb(_simb),value(_value),def(_def),is_const(false),lista_end(_lista_end) {}
    _smb(const string _simb, const int _value,const bool _def):
        simb(_simb),value(_value),def(_def), is_const(false) {}
    friend ostream& operator<<(ostream& os,const _smb& it)
    {
        os << it.simb << ' ';
        os << it.value << ' ';
        os << it.def   << ' ';
        os << it.is_const  << ' ';
        for(unsigned int i=0; i<it.lista_end.size(); i++)
        {
            os << it.lista_end[i];
            if(i!=it.lista_end.size()-1)
            {
                os << "->";
            }
        }
        return os;
    }
} smb_t;
typedef vector<smb_t> tsmb_t;

typedef struct sum_t
{
    string simb;
    int signal;
    int position;
    sum_t() {}
    sum_t(const string _simb, int _signal, const int _position):
        simb(_simb),signal(_signal),position(_position) {}
    friend ostream& operator<<(ostream& os,const sum_t& it)
    {
        os << it.simb << ' ';
        os << it.position << ' ';
        return os;
    }
} sum_t;
typedef vector<sum_t> tsum_t;

typedef struct _inst
{
    string inst_name;
    unsigned int inst_hex;
    unsigned int tam_inst;
    unsigned int qtd_operandos;
    _inst() {}
    _inst(const string _inst_name,const unsigned int _inst_hex,unsigned int _tam_inst,unsigned int _qtd_operandos):
        inst_name(_inst_name),inst_hex(_inst_hex),tam_inst(_tam_inst),qtd_operandos(_qtd_operandos) {}
    friend ostream& operator<<(ostream& os,const _inst& it)
    {
        os << it.inst_name << ' ' << it.inst_hex << ' ' << it.tam_inst << ' ' << it.qtd_operandos;
        return os;
    }
} inst_t;
typedef vector<inst_t> tinst_t;
typedef struct _linha
{
    int nlinha;
    vector<string> tokens;
    _linha() {}
    _linha(int _nlinha, vector<string> _tokens):
        nlinha(_nlinha),tokens(_tokens) {}
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
} linha_t, Linha;
typedef vector<linha_t> code_t;

struct Macro
{
    string label;
    code_t text_code;
    Macro() {}
    Macro(string _label, code_t _text_code) : label(_label), text_code(_text_code) { }
};

typedef struct _define
{
    string label;
    int value;
    _define() {}
    _define(string _label,int _value):
        label(_label),value(_value) {}
    friend bool operator==(_define& define1, _define& define2)
    {
        return (define1.label == define2.label);
    }
    friend ostream& operator<<(ostream& os, const _define& it)
    {
        os << it.label << ' ' << it.value;
        return os;
    }
} define_t, Define;
typedef struct _erro
{
    int nlinha;
    string type;
    string reason;
    _erro() {}
    _erro(int _nlinha,string _type,string _reason):
        nlinha(_nlinha),type(_type),reason(_reason) {}
    friend ostream& operator<<(ostream& os,const _erro& it)
    {
        os << "erro : linha "<<it.nlinha << ", devido a " << it.type << ", pois " << it.reason;
        return os;
    }
} erro_t, Erro;
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
extern string MACRO_no_label;
extern string MACRO_label_no_delimiter;
extern string MACRO_endless;
extern string COMP_COPY_VIRGULA;
extern string COMP_EXPR_INCORRETA;
extern string COMP_QTD_OPERANDOS_INV;
}
namespace sections
{
extern string S;
extern string TEXT;
extern string DATA;
}
namespace instructions
{
extern inst_t ADD;
extern inst_t SUB;
extern inst_t MULT;
extern inst_t DIV;
extern inst_t JMP;
extern inst_t JMPN;
extern inst_t JMPP;
extern inst_t JMPZ;
extern inst_t COPY;
extern inst_t LOAD;
extern inst_t STORE;
extern inst_t INPUT;
extern inst_t OUTPUT;
extern inst_t STOP;
extern unsigned int tamanhoGeral;
extern unsigned int tamanhoCOPY;
extern unsigned int tamanhoSTOP;
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
