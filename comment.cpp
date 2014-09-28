#include "comment.h"
Comment::Comment(string _comment)
{
    setValor(_comment);
}

void Comment::validar(string _comment)
{
    size_t found = _comment.find_first_of(";");
	if(found==string::npos)
	{
	     throw invalid_argument("Rotulo invalido.");
	}
}
