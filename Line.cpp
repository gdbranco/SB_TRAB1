#include "Line.h"
/*--------------------------*/
using namespace std;
/*-------------------------*/
Line::Line(vector<string> _tokens,int _linha=-1):
	n_linha(_linha),tokens(_tokens)
{}

void Line::set_n_Linha(const int& _linha)
{
	this->n_linha = _linha;
}

void Line::set_Tokens(const vector<string>& _tokens)
{
	this->tokens = _tokens;
}
