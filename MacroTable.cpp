#include "MacroTable.h"
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>


/*Cria a macro em uma linha referenciada pelo iterator code_it e guarda na tabela interna do objeto.*/
std::vector<Linha>::iterator MacroTable::create_macro(std::vector<Linha>::iterator &it, std::vector<Linha> &code, std::vector<Erro> &erros_list) {
	std::string name;
	std::vector<Linha> macro_body;
	bool success = false;
	std::vector<Linha> macro_result;
	Macro new_macro;

	if((*it).tokens[1] != "MACRO") {
		erros_list.push_back(Erro(it->nlinha,erros::SEMANTICO,erros::MACRO_no_label));
		return code.end();

	} else if(!PARSER::islabel((*it).tokens[0])) {
		erros_list.push_back(Erro(it->nlinha,erros::SEMANTICO,erros::MACRO_label_no_delimiter));
		return code.end();

	} else {
		name = (*it).tokens[0];
		name.erase(name.end() - 1);

		it++;

	/*	Vai adicionando as linhas na variável de corpo da macro até encontrar "endmacro".
		Incrementa o iterador ao fazer isso.
		Se chegar ao final sem encontrar o "endmacro" (success = false), um erro ocorre. */
		while(it != code.end()) {
			std::vector<string>::iterator aux;
			aux = std::find((*it).tokens.begin(), (*it).tokens.end(), "END");
			if( aux == (*it).tokens.end()) {
				macro_body.push_back((*it));
				it++;

			} else {
				success = true;
				break;
			}
		}

		if (not success) {
			erros_list.push_back(Erro(it->nlinha,erros::SEMANTICO,erros::MACRO_endless));
			return code.end();
		}

		new_macro = Macro(name, macro_body);
	 	this->macros.push_back(new_macro);
		
	}
	return it;
}

 /* Função que retorna o corpo de uma macro.
  * Recebe o iterador referente à linha da chamada da macro. */
std::vector<Linha> MacroTable::get_macro(std::vector<Linha>::iterator it) {
	std::string macro_name;
	std::vector<Macro>::iterator macro_it;
	std::vector<Linha> macro_body;

	/*Pega o nome da macro e seus argumentos. Resolve caso tenha label.*/
	if (PARSER::islabel((*it).tokens[0])) {
		macro_name = (*it).tokens[1];
	} else {
		macro_name = (*it).tokens[0];
	}
	
	/*Procura pela macro*/
	macro_it = this->macros.begin();
	while(macro_it != this->macros.end()) {
		if (((*macro_it).getLabel() == macro_name)) {
			macro_body = (*macro_it).getText_code();
			break;
		}
		macro_it++;
	}

	return macro_body;

}

/*Confere se possui a macro*/
bool MacroTable::has(std::string name) {
	std::vector<Macro>::iterator it;
	it = this->macros.begin();

	while(it != this->macros.end()) {
		if((*it).getLabel() == name) {
			return true;
		}
		it++;
	}

	return false;
}
