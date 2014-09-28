#ifndef COM_H
#define COM_H
#include <string>
#include "Basico.h"
using namespace std;
class Comment:public TipoBasico
{
private:
    void validar(string _comment);
public:
    Comment(){}
    Comment(string _comment);
};
#endif // COM_H
