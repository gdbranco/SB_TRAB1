#ifndef PARSER_H
#define PARSER_H
#define OK 1
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <utility>
#include "defines.h"
#include <fstream>
using namespace std;
class PARSER
{
private:
public:
    static int islabel(string _label);
    static int isdir(string _dir);
    static int isinst(string _inst);
    static int iscomment(string _comment);
    static void pre_proc(string _arquivo);
};
#endif // PARSER_H