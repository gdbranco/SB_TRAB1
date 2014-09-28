#include "Macro.h"
Macro::Macro(string _label,string _text_code)
{
    setValor(_label);
    setText_code(_text_code);
}

void Macro::validar(string _label)
{

}

ostream& operator<<(ostream& os, const Macro& it)
{
    os << it.getValor() << ' ' << it.text_code;
    return os;
}
