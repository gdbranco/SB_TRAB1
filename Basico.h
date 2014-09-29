#ifndef BASICO_H
#define BASICO_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class TipoBasico
{
private:
	virtual void validar(string)=0;
protected:
	string valor;
public:
	void setValor(string);
	string getValor() const;
};
inline string TipoBasico::getValor() const
{
	return valor;
}

inline void TipoBasico::setValor(string _valor)
{
    validar(_valor);
	this->valor = _valor;
}
#endif
