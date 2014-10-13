#ifndef MACRO_H
#define MACRO_H
#include <string>
#include <iostream>
#include <vector>
#include "defines.h"

using namespace std;

class Macro 
{
private:
    vector<Linha> text_code;
	string label;
    void validar(string _label);
public:
    Macro(){}
    Macro(string _label, vector<Linha> _text_code);
    void setText_code(vector<Linha> _text_code);
    vector<Linha> getText_code();
	std::string getLabel();
	void setLabel(std::string _label);
};


inline std::string Macro::getLabel()
{
    return (this->label);
}

inline void Macro::setLabel(string _label)
{
    this->label = _label;
}

inline vector<Linha> Macro::getText_code()
{
    return (this->text_code);
}

inline void Macro::setText_code(vector<Linha> _text_code)
{
    this->text_code = _text_code;
}


#endif // MACRO_H
