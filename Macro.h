#ifndef MACRO_H
#define MACRO_H
#include <string>
#include <iostream>
#include <vector>
#include "defines.h"

using namespace std;

struct Macro 
{
    vector<Linha> text_code;
	string label;
    Macro(){}
    Macro(string _label, vector<Linha> _text_code);
};

Macro::Macro(string _label, std::vector<Linha> _text_code)
{
    setLabel(_label);
    setText_code(_text_code);
}
#endif // MACRO_H
