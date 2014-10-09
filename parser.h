#ifndef PARSER_H
#define PARSER_H
#define OK 1
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include "defines.h"
#include <fstream>
//TODO:
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
    friend ostream& operator<<(ostream& os, const _define& it)
    {
        os << it.label << ' ' << it.value;
        return os;
    }
}Define;
class PARSER
{
private:
    vector<Define> defines;
    vector<Linha> make_listaEQU(vector<Linha>& code);
public:
    static int islabel(const string _label);
    static int isdir(const string _dir);
    static int isinst(const string _inst);
    static int iscomment(const string _comment);
    static vector<Linha> pre_proc(const vector<Linha> _code);
    static void memgetline(const Linha, string& s);
    static vector<Linha> toMEM(const string nome);
    static string retiraComentarios(string _linha);
    static vector<pair<int,string> > erros;
};
#endif // PARSER_H
