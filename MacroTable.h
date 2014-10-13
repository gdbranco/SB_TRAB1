#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H 

#include <vector>
#include <string>
#include "Macro.h"
#include "defines.h"
#include "parser.h"

class MacroTable {
private:
	std::vector<Macro> macros;

public:
	MacroTable() {}
	std::vector<Linha>::iterator  create_macro(std::vector<Linha>::iterator &code_it, std::vector<Linha> &code, std::vector<Erro> &erros_list);
	std::vector<Linha> get_macro(std::vector<Linha>::iterator it);
	bool has(std::string name);

};

#endif //MACRO_TABLE_H
