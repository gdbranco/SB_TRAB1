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
    vector<define_t> defines_list;
    tsmb_t simb_list;
    code_t make_listaEQU(code_t _code);
    code_t preproc(code_t _code);
    code_t passagiunics(code_t code);
    int define_exists(const define_t procura);
public:
    static vector<erro_t> erros_list;
    /**Metodos**/
    static int islabel(const string _label);
    static int isdir(const string _dir);
    static int isinst(const string _inst);
    static int iscomment(const string _comment);
    static code_t run_preproc(code_t _code);
    static code_t run_montador(code_t code);
    static code_t toMEM(const string nome);
    static string retiraComentarios(string _linha);
};
#endif // PARSER_H
