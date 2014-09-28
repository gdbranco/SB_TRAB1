#ifndef OPERANDO_H
#define OPERANDO_H
#include <string>
#include "Basico.h"
using namespace std;
class Operando:public TipoBasico
{
private:
    void validar(string _nome);
public:
    Operando(){}
    Operando(string _nome);
    friend ostream& operator<<(ostream& os, const Operando& it);
};
#endif // OPERANDO_H

