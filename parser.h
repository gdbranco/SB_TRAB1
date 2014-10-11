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
#include <sstream>
//TODO:
using namespace std;
class PARSER
{
private:
    vector<Define> defines_list;
    vector<Linha> make_listaEQU(vector<Linha> _code);
    vector<Linha> run_preproc(vector<Linha> _code);
    int define_exists(Define procura);
public:
    static vector<Erro> erros_list;
    /**Metodos**/
    static int islabel(const string _label);
    static int isdir(const string _dir);
    static int isinst(const string _inst);
    static int iscomment(const string _comment);
    static vector<Linha> pre_proc(const vector<Linha> _code);
    static void memgetline(const Linha, string& s);
    static vector<Linha> toMEM(const string nome);
    static string retiraComentarios(string _linha);
};
#endif // PARSER_H
