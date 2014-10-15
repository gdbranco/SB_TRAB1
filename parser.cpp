#include "parser.h"
vector<erro_t> PARSER::erros_list;
tinst_t PARSER::instruction_list;
string PARSER::retiraComentarios(string _linha)
{
	size_t found = _linha.find(';');
	if(found!=string::npos)
	{
		//        cout << _linha << endl;
		//        cout << found;
		//        cin.get();
		if(found == 0)
		{
			_linha = "";
		}
		else
		{
			_linha = _linha.substr(0,found-1);
		}
	}
	return _linha;
}

void PARSER::inicializa_paradas()
{
	instruction_list.push_back(instructions::ADD);
	instruction_list.push_back(instructions::SUB);
	instruction_list.push_back(instructions::MULT);
	instruction_list.push_back(instructions::DIV);
	instruction_list.push_back(instructions::JMP);
	instruction_list.push_back(instructions::JMPN);
	instruction_list.push_back(instructions::JMPP);
	instruction_list.push_back(instructions::JMPZ);
	instruction_list.push_back(instructions::COPY);
	instruction_list.push_back(instructions::LOAD);
	instruction_list.push_back(instructions::STORE);
	instruction_list.push_back(instructions::INPUT);
	instruction_list.push_back(instructions::OUTPUT);
	instruction_list.push_back(instructions::STOP);
}

code_t PARSER::toMEM(string nome_arq)
{
	inicializa_paradas();
	code_t memoria;
	vector<string> _tokens;
	int _linha=0;
	fstream sc;
	char* pch;
	sc.open(nome_arq.c_str());
	string s;
	while(getline(sc,s))
	{
		_linha++;
		s = retiraComentarios(s);
		if(s!="")
		{
			pch = strtok((char*)s.c_str(),"\t ");
			while(pch!=NULL)
			{
				transform(pch,pch+strlen(pch),pch,static_cast<int(*)(int)>(toupper));
				_tokens.push_back(string(pch));
				//                cout << pch << endl;
				pch = strtok(NULL,"\t ");
			}
			memoria.push_back(linha_t(_linha,_tokens));
		}
		_tokens.clear();
	}
	sc.close();
	return memoria;
}
code_t PARSER::preproc(code_t _code)
{
	bool erase_currentline;
	bool erase_nextline;
	bool erro;
	bool achei;
	code_t code = _code;
	code_t::iterator linha = code.begin();
	vector<string>::iterator token;
	vector<define_t>::iterator define;
	if(!code.empty())
	{
		while(linha!=code.end())
		{
			erase_currentline = false;
			erase_nextline    = false;
			//cout << define->label;
			//cout << define->label.length();
			//cout << define->label.substr(0,define->label.length()-1);
			//cin.get();
			/**Checa se a linha eh um IF e se a proxima é valida**/
			if((find(linha->tokens.begin(),linha->tokens.end(),diretivas::IF)!=linha->tokens.end()))
			{
				//                cout << *linha;
				//                cin.get();
				token = linha->tokens.begin();
				/**Substitui os labels definidos na linha do IF por seu valor EQU**/
				while(token != linha->tokens.end())
				{
					achei = false;
					define = defines_list.begin();
					while(define!=defines_list.end() && !achei)
					{
						erro=false;
						//                        cout <<"label : " << define->label;
						//                        cin.get();
						stringstream ss;
						ss << define->value;
						if(*token == define->label.substr(0,define->label.length()-1))
						{
							//                            cout <<"pre-troca : " << *token;
							//                            cin.get();
							*token = ss.str();
							//                            cout <<"pos-troca : " <<*token;
							//                            cin.get();
							achei = true;
						}
						/**Se a linha nao for um EQU definido e nao for uma diretiva a definicao nao existe**/
						else
						{
							if(!isdir(*token))
							{
								//                                cout << "token nao eh dir nem definido : " << *token;
								//                                cin.get();
								erro = true;
							}
						}
						define++;
					}
					token++;
				}
				/**Se houver erro o coloca na lista**/
				if(erro)
				{
					erros_list.push_back(erro_t(linha->nlinha,erros::SEMANTICO,erros::EQU_ndefinida)); //EQU nao definida
				}
				token = linha->tokens.begin();
				/**Se nao houver erros faz a avaliacao do IF**/
				while(token != linha->tokens.end() && !erro)
				{
					//                    cout << *token;
					//                    cin.get();
					if(*token == diretivas::IF) //Essa condicao é inutil, retirar depois
					{
						erase_currentline = true;
					}
					else if(*token == "0")
					{
						erase_nextline = true;
					}
					token++;
				}
				if(erase_nextline)
				{
					code.erase(linha+1);
				}
				if(erase_currentline)
				{
					code.erase(linha);
				}
			}
			/**Tenta substituir caso um define seja achado fora de um IF**/
			else
			{
				define = defines_list.begin();
				while(define!=defines_list.end())
				{
					if(find(linha->tokens.begin(),linha->tokens.end(),define->label.substr(0,define->label.length()-1))!=linha->tokens.end())
					{
						token = linha->tokens.begin();
						while(token!=linha->tokens.end())
						{
							if(*token == define->label.substr(0,define->label.length()-1))
							{
								stringstream ss;
								ss << define->value;
								*token = ss.str();
							}
							token++;
						}
					}
					define++;
				}
			}
			//cout<< *linha<<endl;
			//cin.get();
			if(!erase_currentline)
				linha++;
		}
	}
	return code;
}
code_t PARSER::make_listaEQU(code_t _code)
{
	code_t code = _code;
	code_t::iterator linha = code.begin();
	vector<string>::iterator token;
	bool erased;
	bool labeled;
	bool EQU;
	int label_counter;
	int value;
	int erro;
	string label;
	if(!code.empty())
	{
		//Procura SECTION DATA
		while(linha!=code.end())
		{
			if((find(linha->tokens.begin(),linha->tokens.end(),diretivas::SECTION) != linha->tokens.end()) \
					&& \
					(find(linha->tokens.begin(),linha->tokens.end(),diretivas::DATA) != linha->tokens.end()))
			{
				linha++;
				break; // Sai do loop com a linha no local correto SECTION DATA
			}
			linha++;
		}
		/**Procura as labels**/
		while(linha!=code.end())
		{
			erased = false;
			labeled = false;
			EQU = false;
			erro = 0;
			label.clear();
			label_counter=0;
			token = linha->tokens.begin();
			while(token!=linha->tokens.end())
			{
				//                cout << *token;
				//                cin.get();
				if(islabel(*token))
				{
					label = *token;
					labeled = true;
					label_counter++;
				}
				else if(token->find(diretivas::EQU)!=string::npos)
				{
					EQU = true;
				}
				else
				{
					value = atoi(token->c_str());
				}
				token++;
			}
			/**Apos passar pela linha pode-se tentar montar um define**/
			if(EQU)
			{
				if(labeled)
				{
					if(label_counter<2)
					{
						define_t _aux(label,value);
						if(!define_exists(_aux))
						{
							defines_list.push_back(_aux);
							code.erase(linha);
							erased = true;
						}
						else
						{
							erro = 1; //Label ja definida
						}
					}
					else
					{
						erro = 2; //Mais de um label na linha
					}
				}
				else
				{
					erro = 3; //EQU sem label
				}
			}
			/**Adiciona os erros a lista de erros**/
			switch(erro)
			{
				case 1:
					erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::label_redefinida));
					break;
				case 2:
					erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::label_dupla));
					break;
				case 3:
					erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::EQU_nlabeled));
					break;
				default:
					//Sem erros
					break;
			}
			if(!erased)
				linha++;
		}
		/**Mostrando o vetor para testes**/
		//        vector<define_t>::iterator it = defines_list.begin();
		//        while(it!=defines_list.end())
		//        {
		//            cout << *it<< endl;
		//            it++;
		//        }

	}
	return code;
}
code_t PARSER::run_preproc(code_t code)
{
	PARSER p;
	code = p.make_listaEQU(code);
	code = p.preproc(code);
	return code;
}

code_t PARSER::passagem_macros(code_t _code) {
	code_t::iterator it;
	code_t::iterator m_beg, m_end;
	code_t macro_result;
	code_t code(_code); 
	MacroTable mct;

	it = code.begin();
	while(it != code.end()) {
		/*Se a linha possui "macro", é uma declaração que deve ser colocada na tabela.*/
		if (std::find(it->tokens.begin(), it->tokens.end(), "MACRO") != it->tokens.end()) {
			/*Guarda o indice do iterador para recuperá-lo após apagar do vetor*/
			int aux = code.begin() - it;
			m_beg = it;
			m_end = mct.create_macro(it, code, erros_list);
			if(m_end != code.end()) {
				code.erase(m_beg, m_end + 1);
			}
			it = code.begin() + aux;


			/*Caso contrário, confere se possui label e declaração e substitui o código.*/
		} else if (  (PARSER::islabel(it->tokens[0])) && mct.has(it->tokens[1])  ) {
			macro_result = mct.get_macro(it); 
			code.erase(it);
			code.insert(it, macro_result.begin(), macro_result.end());

			/*Substitui a chamada pelo corpo da macro*/
		} else if (  mct.has(it->tokens[0])  ) {
			macro_result = mct.get_macro(it); 
			code.erase(it);
			code.insert(it, macro_result.begin(), macro_result.end());

		} 
		it++;
	}
	return code;
}

/**Metodo montador**/
code_t PARSER::passagiunics(code_t code)
{
	unsigned int PC=0;
	code_t _code = code;
	vector<int> obj_code;
	code_t::iterator linha = _code.begin();
	unsigned int increment_add;
	bool space_found,const_found, is_soma;
	//unsigned int counter,counter_operadores;
	while(linha!=_code.end())
	{
		space_found = false;
		const_found = false;
		is_soma = false;
		cout << PC << ' ';
		//cout << linha->nlinha << ' ' << *linha << endl;
		vector<string>::iterator token = linha->tokens.begin();
		while(token!=linha->tokens.end()) 
		{
			inst_t rinst;
			increment_add = 1; //Ao chegar num novo token o incremento do endereco eh sempre 1
			cout << *token << ' ';
			//cout << PC << ' ' << *token << ' ';
			/**
			  Logica para tratar token a token
Done: se label, se instruction, se diretiva, tabela de simbolos, codigo objeto
TODO: erros e soma de indices
			 **/
			if ((*token) == "+")
			{
				if (token == linha->tokens.end())
				{
					//erro
				} else {
					is_soma = true;
				}	
				increment_add = 0; 
			} else if (is_soma)
			{
				increment_add = 0;
				if (isNumber(*token))
				{
					obj_code[obj_code.size() - 1] += atoi(token->c_str());
				} else {
					int i = symbol_exists(token->substr(0, (*token).size() - 1));
					if (i > -1)
					{
						if(simb_list[i].def) {
							obj_code[obj_code.size() - 1] += simb_list[i].value;
						} else {
							simb_list[i].def = true;
							simb_list[i].value = PC;
						}
						
					} else {
						simb_list.push_back(smb_t((*token), PC, true));
					}

				}
			} else 	if(islabel(*token))
			{
				increment_add = 0; //Se for uma label não aumenta o endereço
				int i = symbol_exists(token->substr(0, (*token).size() - 1));
				if (i > -1)
				{
					if(simb_list[i].def) {
						//erro
					} else {
						simb_list[i].def = true;
						simb_list[i].value = PC;
					}
					
				} else {
					simb_list.push_back(smb_t((*token), PC, true));
				}
			}
			else if(isinst(*token,rinst)) /**Refazer para melhorar a estrutura de instrucoes e diretivas**/
			{
				//cout << "\nAchei inst : "<< *token << endl;
				increment_add = rinst.qtd_operandos;
				obj_code.push_back(rinst.inst_hex);
			}
			else if(isdir(*token))
			{
				increment_add=0;
				//cout << "Achei dir : " << *token;
				if(*token == diretivas::SPACE)
				{
					//cout << "Achei space";
					space_found = true;
					increment_add=1;
					obj_code.push_back(0);
				}
				else if(*token == diretivas::CONST)
				{
					const_found = true;
				}
			}
			else if(isSymbol(*token)) {
				int i = symbol_exists(*token);
				if (i > -1)
				{
					if(simb_list[i].def) {
						//nada
					} else {
						simb_list[i].lista_end.push_back(PC);
						obj_code.push_back(0);
					}
					
				} else {
					std::vector<int> index_list;
					index_list.push_back(PC);
					simb_list.push_back(smb_t((*token), 0, false, index_list));
					obj_code.push_back(0);
				}
					
			}
			else if(space_found)
			{
				if(token!=linha->tokens.end())
				{
					increment_add = atoi(token->c_str())-1;
					for(unsigned int i=0;i<increment_add;i++)
					{
						obj_code.push_back(0);
					}
				}
			}
			else if(const_found)
			{
				obj_code.push_back(atoi(token->c_str()));
			}
			token++;
			PC+=increment_add; /**Nao pode contar diretivas**/
		}
		cout << endl;
		linha++;
	}
	cout << "END FINAL : " << PC << endl;
	cout << "Nome, Valor, def, Lista de uso" << endl; 
	for (int i = 0; i < (int) simb_list.size(); ++i)
	{
		cout << simb_list[i] << endl;	
	}
	for(unsigned int i=0;i<simb_list.size();i++)
	{
		for(unsigned int j=0;j<simb_list[i].lista_end.size();j++)
		{
			obj_code[simb_list[i].lista_end[j]] += simb_list[i].value;
		}
	}
	for(unsigned int i=0;i<obj_code.size();i++)
	{
		cout << obj_code[i];
		if(i!=obj_code.size()-1)
		{
			cout << endl;
		}
	}
	return _code;
}

code_t PARSER::run_macros(code_t code)
{
	PARSER p;
	code = p.passagem_macros(code);
	return code;
}

code_t PARSER::run_montador(code_t code)
{
	PARSER p;
	code = p.passagiunics(code);
	return code;
}
int PARSER::define_exists(define_t procura)
{
	vector<define_t>::iterator define;
	if(!defines_list.empty())
	{
		define = defines_list.begin();
		while(define!=defines_list.end())
		{
			if(*define == procura)
			{
				return OK;
			}
			define++;
		}
	}
	return !OK;
}

int PARSER::symbol_exists(string procura)
{
	for (int i = 0; i < (int) simb_list.size(); ++i)
	{
		if (simb_list[i].simb == procura)
		{
			return i;
		}
	}
	return -1;
}

int PARSER::islabel(string _label)
{
	size_t found=_label.find(':');
	if(found && _label[found+1] == '\0')
		return OK;
	return !OK;
}

int PARSER::iscomment(string _comment)
{
	size_t found;
	if((found = _comment.find(';')!=string::npos))
		return OK;
	return !OK;
}
int PARSER::isdir(string _dir)
{
	if(_dir == diretivas::SECTION ||
		_dir == diretivas::TEXT    ||
		_dir == diretivas::DATA    ||
		_dir == diretivas::IF      ||
		_dir == diretivas::EQU     ||
		_dir == diretivas::END     ||
		_dir == diretivas::CONST   ||
		_dir == diretivas::SPACE   ||
		_dir == diretivas::MACRO)
	{
		return OK;
	}
	return !OK;
}

bool PARSER::isSymbol(string simb) {
	string valid = "ABCDEFGHIJKLMNOPQRSTUVXYZ_0987654321";
	string beg_valid = valid.substr(0,26);
	int i = 0;
	if (beg_valid.find(simb[0]) ==  string::npos)
	{
		return false;	
	} else {
		for (i = 0; i < (int) simb.size(); ++i)
		{
			if (valid.find(simb[i]) == string::npos)
			{
				return false;
			}
		}
	}
	return true;
}

bool PARSER::isNumber(string simb) {
	string valid = "0987654321";
	int i = 0;
	for (i = 0; i < (int) simb.size(); ++i)
	{
		if (valid.find(simb[i]) == string::npos)
		{
			return false;
		}
	}
	return true;
}

//retorno = (inst valida) ? inst.opcode : 1
bool PARSER::isinst(string _inst,inst_t& rinst)
{
	bool achei = false;
	tinst_t::iterator inst_cur=instruction_list.begin();
	while(inst_cur!=instruction_list.end() && !achei)
	{
		if(inst_cur->inst_name == _inst)
		{
			rinst = *inst_cur;
			achei = true;
		}
		inst_cur++;
	}
	return achei;
}
