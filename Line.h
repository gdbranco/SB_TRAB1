#ifndef LINES_H
#define LINES_H
/*---------------------*/
#include<vector>
#include<string>
#include "Rot.h"
#include "Operador.h"
#include "Operando.h"
#include "comment.h"
/*---------------------*/
using namespace std;
/*---------------------*/
class Line
{
private:
	int nlinha;
	Rotulo label;
	Operador op;
	vector<Operando> to_op;
	//Comment ignore;
	//vector<string> tokens;
public:
    Line(){};
    Line(Rotulo _label,Operador _op,vector<Operando> _to_op,int _linha);
    /*Gets*/
    int getNlinha() const;
    Rotulo getRotulo() const;
    Operador getOperador() const;
    vector<Operando> getOperandos() const;
    /*Sets*/
    void setNlinha(const int& _linha);
    void setRotulo(const Rotulo& _rot);
    void setOperador(const Operador& _op);
    void setOperandos(const vector<Operando>& _to_op);
    /*Output*/
    friend ostream& operator<<(ostream& os, const Line& it);
};


inline int Line::getNlinha() const
{
	return this->nlinha;
}

inline Rotulo Line::getRotulo() const
{
    return this->label;
}

inline Operador Line::getOperador() const
{
    return this->op;
}

inline vector<Operando> Line::getOperandos() const
{
    return this->to_op;
}
#endif
