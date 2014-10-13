#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include "macros.h"

/*Remover definições de macros!*/
vector<Erro> passagem_macros(std::vector<Linha> &code) {
	std::vector<Linha>::iterator it;
	std::vector<Linha>::iterator m_beg, m_end;
	std::vector<Linha> macro_result;
	vector<Erro> erros_list;
	MacroTable mct;

	it = code.begin();
	while(it != code.end()) {
		/*Se a linha possui "macro", é uma declaração que deve ser colocada na tabela.*/
		if (std::find((*it).tokens.begin(), (*it).tokens.end(), "MACRO") != (*it).tokens.end()) {
			/*Guarda o indice do iterador para recuperá-lo após apagar do vetor*/
			int aux = code.begin() - it;
			m_beg = it;
			m_end = mct.create_macro(it, code, erros_list);
			if(m_end != code.end()) {
				code.erase(m_beg, m_end + 1);
			}
			it = code.begin() + aux;
			

		/*Caso contrário, confere se possui label e declaração e substitui o código.*/
		} else if (  (PARSER::islabel((*it).tokens[0])) && mct.has((*it).tokens[1])  ) {
			macro_result = mct.get_macro(it); 
			code.erase(it);
			code.insert(it, macro_result.begin(), macro_result.end());

		/*Substitui a chamada pelo corpo da macro*/
		} else if (  mct.has((*it).tokens[0])  ) {
			macro_result = mct.get_macro(it); 
			code.erase(it);
			code.insert(it, macro_result.begin(), macro_result.end());

		} 
		it++;
	}
	return erros_list;
}


