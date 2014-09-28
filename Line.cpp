#include "Line.h"
/*--------------------------*/
using namespace std;
/*-------------------------*/
Line::Line(Rotulo _label,Operador _op,vector<Operando> _to_op,int _linha=-1):
	nlinha(_linha),label(_label),op(_op)
{
    setOperandos(_to_op);
}

void Line::setNlinha(const int& _linha)
{
	this->nlinha = _linha;
}

//void Line::set_Tokens(const vector<string>& _tokens)
//{
//	this->tokens = _tokens;
//}

void Line::setOperador(const Operador& _op)
{
    this->op = _op;
}

void Line::setOperandos(const vector<Operando>& _to_op)
{
    this->to_op = _to_op;
}

void Line::setRotulo(const Rotulo& _label)
{
    this->label = _label;
}

ostream& operator<<(ostream& os, const Line& it)
{
    os << it.label << ' ' << it.op << ' ';
    for(unsigned int i=0;i<it.to_op.size();i++)
    {
        cout << it.to_op.at(i) << ' ';
    }
    return os;
}
