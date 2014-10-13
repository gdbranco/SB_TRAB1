#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Macro.h"
#include "MacroTable.h"
#include "macros.h"
#include "parser.h"
#include "defines.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	string line;
	Linha linha_pronta;
	std::vector<string> tokens;
	std::vector<Linha> code_vector;
	/*std::stringstream buffer;*/
	string code_str = "";
	vector<Erro> erros_list;

	/*std::ifstream code_file("teste.asm");

	if (code_file.is_open()) {
		while(getline(code_file, line)) {
			code_str += line;
			code_str += "\n";
		}
	}

	cout << code_str;*/

	code_vector = PARSER::toMEM("teste.asm");

	erros_list = passagem_macros(code_vector);

	vector<Linha>::iterator it = code_vector.begin();
	while(it != code_vector.end()) {
		cout << *it << endl;
		it++;
	}

	cout << "=================" << endl;

	vector<Erro>::iterator e_it = erros_list.begin();

	while(e_it != erros_list.end()) {
		cout << *e_it << endl;
		e_it++;
	}

	return 0;
}
