#include "Macro.h"
Macro::Macro(string _label,string _text_code)
{
    setRotulo(_label);
    setText_code(_text_code);
}

void Macro::setRotulo(string _label)
{
    this->label = Rotulo(_label);
}

Rotulo Macro::getRotulo()
{
    return this->label;
}

ostream& operator<<(ostream& os, const Macro& it)
{
    os << it.label << ' ' << it.text_code;
    return os;
}
