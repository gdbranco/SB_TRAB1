#ifndef MACRO_H
#define MACRO_H
#include <string>
#include "Rot.h"
using namespace std;
class Macro:public TipoBasico
{
private:
    string text_code;
    void validar(string _label);
public:
    Macro(){}
    Macro(string _label, string _text_code);
    void setText_code(string _text_code);
    string getText_code();
    friend ostream& operator<<(ostream& os, const Macro& it);
};

inline string Macro::getText_code()
{
    return (this->text_code);
}

inline void Macro::setText_code(string _text_code)
{
    this->text_code = _text_code;
}
#endif // MACRO_H
