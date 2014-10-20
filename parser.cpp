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

code_t PARSER::passagem_macros(code_t _code)
{
    code_t::iterator it;
    code_t::iterator m_beg, m_end;
    code_t macro_result;
    code_t code(_code);
    MacroTable mct;

    it = code.begin();
    while(it != code.end())
    {
        /*Se a linha possui "macro", é uma declaração que deve ser colocada na tabela.*/
        if (std::find(it->tokens.begin(), it->tokens.end(), "MACRO") != it->tokens.end())
        {
            /*Guarda o indice do iterador para recuperá-lo após apagar do vetor*/
            int aux = code.begin() - it;
            m_beg = it;
            m_end = mct.create_macro(it, code, erros_list);
            if(m_end != code.end())
            {
                code.erase(m_beg, m_end + 1);
            }
            it = code.begin() + aux;


            /*Caso contrário, confere se possui label e declaração e substitui o código.*/
        }
        else if (  (PARSER::islabel(it->tokens[0])) && mct.has(it->tokens[1])  )
        {
            macro_result = mct.get_macro(it);
            code.erase(it);
            code.insert(it, macro_result.begin(), macro_result.end());

            /*Substitui a chamada pelo corpo da macro*/
        }
        else if (  mct.has(it->tokens[0])  )
        {
            macro_result = mct.get_macro(it);
            code.erase(it);
            code.insert(it, macro_result.begin(), macro_result.end());

        }
        it++;
    }
    return code;
}

/**Metodo montador**/
/**TODO: Erros
  **	Declaração ausente
  **	Declaração repetida
  **	Diretiva inválida
  **	Instrução inválida
  **	Diretiva ou instrução na sessão errada
  **	Rótulo duplo na mesma linha
  **	Seção faltante
  **	Tipo de argumento inválido
  *	Pulo para rótulo inválido
  *	Divisão por zero
  *	Endereço de memória não reservado
  ** Modificado const**/
vector<int> PARSER::passagem_unica(code_t code)
{
    unsigned int PC=0;
    int sinal;
    code_t _code = code;
    vector<int> obj_code;
	vector<int> mod_const; //Array de posições em que um const é modificado
	vector< mem_acc_t > mem_access_list;
    tsum_t sum_list;
    code_t::iterator linha = _code.begin();
    tsmb_t::iterator last_symbol;
    std::vector<string>::iterator cp_iter;
	short check_sessions = 0;
    unsigned int increment_add;
    bool space_found, const_found, is_soma, has_label;
	bool section_text = true;
	bool last_inst_mem_changer;
	bool last_inst_div;
	bool last_inst_jmp;
	int end_first_section = 0;
	bool text_first=true;

    while(linha!=_code.end())
    {
        space_found = false;
        const_found = false;
        is_soma = false;
		has_label = false;
		last_inst_mem_changer = false;
		last_inst_div = false;
		last_inst_jmp = false;

        /*Lógica para o COPY funcionar com vírgula */
        cp_iter = find(linha->tokens.begin(), linha->tokens.end(), "COPY");
        if( cp_iter != linha->tokens.end())
        {
			if (*(cp_iter + 2) == "+" || *(cp_iter + 2) == "-") {
				cp_iter += 3;
				if(cp_iter->find_last_of(',') + cp_iter->begin() == cp_iter->end() -1)
				{
					*cp_iter=cp_iter->substr(0, cp_iter->length()-1);
				}
				else
				{
					erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::COMP_COPY_VIRGULA)); 
				}
				
			} else {
				cp_iter++;
				if(cp_iter->find_last_of(',') + cp_iter->begin() == cp_iter->end() -1)
				{
					*cp_iter=cp_iter->substr(0, cp_iter->length()-1);
				}
				else
				{
					erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::COMP_COPY_VIRGULA)); 
				}
			}

        }
        sinal = 1;
        vector<string>::iterator token = linha->tokens.begin();
		/*	Vai iterar na linha, token a token. Vai testar o token numa sequencia ordenada de possibilidades, e agir de acordo com ela.
		 *	A sequencia está na seguinte ordem (e faz toda a diferença)
		 *	Checa se o Token é uma soma ou subtração.
		 *	Checa se uma soma ou subtração no operando já está acontecendo.
		 *	Checa se o token anterior é um space ou const.
		 *	Checa se o token atual se encaixa na definição de label.
		 *	Checa se o token atual é uma instrução válida.
		 *	Checa se o token atual é uma diretiva válida.
		 *	Checa se o token atual é um símbolo válido.
		 *	Caso não seja nenhum desses, vai ser um argumento inválido*/
        while(token!=linha->tokens.end())
        {
            inst_t rinst;
            increment_add = 1; //Ao chegar num novo token o incremento do endereco eh sempre 1


			/*Confere se tem soma ou subtração*/
//TOKEN == +
            if ((*token) == "+")
            {
				if (!section_text) {
                    erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::COMP_EXPR_INCORRETA)); 
				} else {
					/*Confere se a expressão acaba prematuramente*/
					if (token == linha->tokens.end() - 1)
					{
						erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::COMP_EXPR_INCORRETA)); 
					}
					else
					{
						is_soma = true;
					}
				}
                increment_add = 0;
            }
//TOKEN == -
            else if ((*token) == "-")
            {
				if (!section_text) {
                    erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::COMP_EXPR_INCORRETA)); 
				} else {
					/*Confere se a expressão acaba prematuramente*/
					if (token == linha->tokens.end() - 1)
					{
						erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::COMP_EXPR_INCORRETA)); 
					}
					else
					{
						is_soma = true;
						sinal = -1;
					}
				}
                increment_add = 0;
            }
//TOKEN anterior é + ou -
            else if (is_soma)
            {
                increment_add = 0;
				/*Se é numero direto, soma*/
                if (isNumber(*token))
                {
                    obj_code[obj_code.size() - 1] += (sinal)*atoi(token->c_str());
                }
				/*Se não, confere se está definido*/
                else
                {
                    int i = symbol_exists(token->substr(0, (*token).size() - 1));
					/*Se não está, adiciona na lista de somas para ser adicionado depois*/
                    if (i > -1)
                    {
                        if(simb_list[i].def)
                        {
                            if(simb_list[i].is_const)
                            {
                                obj_code[obj_code.size() - 1] += (sinal)*simb_list[i].value;
                            }
                        }
                        else
                        {
                            sum_list.push_back(sum_t(*token, sinal, PC -1));
                        }

                    }
                    else
                    {
                        sum_list.push_back(sum_t(*token, sinal, PC - 1));
                        simb_list.push_back(smb_t((*token), -1, false));
                    }

                }
            }
//TOKEN anterior é SPACE
            else if(space_found)
            {
                if(token!=linha->tokens.end())
                {
					if (isNumber(*token)) {
						increment_add = atoi(token->c_str());
						if (increment_add <= 0) {
							erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO, erros::COMP_ARG_INV)); 
						} else {
							increment_add--;
							for(unsigned int i=0; i<increment_add; i++)
							{
								obj_code.push_back(0);
							}
						}
					} else {
						erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO, erros::COMP_ARG_INV)); 
					}
                }
            }
//TOKEN anterior é CONST
            else if(const_found)
            {
				if (isNumber(*token)) {
					obj_code.push_back(atoi(token->c_str()));
				} else {
					erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO, erros::COMP_ARG_INV)); 
				}
            }
//TOKEN é uma label
            else if(islabel(*token))
            {
                increment_add = 0; //Se for uma label não aumenta o endereço
                int i = symbol_exists(token->substr(0, token->length() - 1));

				if(has_label) {
					erros_list.push_back(erro_t(linha->nlinha,erros::SEMANTICO,erros::label_dupla)); 
				}

				/*Se label ja existe*/
                if (i > -1)
                {
                    if(simb_list[i].def)
                    {
						erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::label_redefinida)); 
                    }
                    else
                    {
                        simb_list[i].def = true;
                        simb_list[i].value = PC;
                        last_symbol = simb_list.begin() + i;
                    }

                }
                else
                {
                    simb_list.push_back(smb_t(token->substr(0,token->length()-1), PC, true));
                    last_symbol = simb_list.end() - 1;
                }
				has_label = true;
            }
//TOKEN é uma instrução
            else if(isinst(*token,rinst)) /**Refazer para melhorar a estrutura de instrucoes e diretivas**/
            {
				/*Confere se a instrução não está na seção de dados*/
				if(!section_text) {
					erros_list.push_back(erro_t(linha->nlinha,erros::SEMANTICO,erros::COMP_INST_SECAO_ERRADA)); 
				}
				/*Confere a quantidade de argumentos*/
				unsigned int line_size = linha->tokens.end() - token;
				if(find(linha->tokens.begin(), linha->tokens.end(), "+") != linha->tokens.end()) {
					line_size -= 2;
				}
				if(find(linha->tokens.begin(), linha->tokens.end(), "-") != linha->tokens.end()) {
					line_size -= 2;
				}

				if (line_size != rinst.qtd_operandos + 1) {
					erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::COMP_QTD_OPERANDOS_INV)); 
				}
                increment_add = 1;
				if(rinst == instructions::STORE ||
				   rinst == instructions::INPUT ||
				   rinst == instructions::COPY)
				{
					last_inst_mem_changer = true;
				}
				else if(rinst == instructions::DIV)
				{
					last_inst_div = true;
				}
				else if(rinst == instructions::JMP ||
						rinst == instructions::JMPN ||
						rinst == instructions::JMPP ||
						rinst == instructions::JMPZ)
				{
					last_inst_jmp = true;
				}
				/*Guarda na lista de código objeto*/
                obj_code.push_back(rinst.inst_hex);
            }
//TOKEN é uma diretiva
            else if(isdir(*token))
            {
                increment_add=0;
                if(*token == diretivas::SPACE)
                {
					/*Confere se a diretiva não está na seção de texto*/
					if(section_text) {
						erros_list.push_back(erro_t(linha->nlinha,erros::SEMANTICO,erros::COMP_DIR_SECAO_ERRADA)); 
					}
                    space_found = true;
                    increment_add=1;
                    obj_code.push_back(0);
                }
                else if(*token == diretivas::CONST)
                {
					/*Confere se a diretiva não está na seção de texto*/
					if(section_text) {
						erros_list.push_back(erro_t(linha->nlinha,erros::SEMANTICO,erros::COMP_DIR_SECAO_ERRADA)); 
					}
                    const_found = true;
                    if(simb_list.size() > 0)
                    {
                        last_symbol->is_const = true;
                    }
				}
				else if(*token == diretivas::SECTION)
				{
					if( *(token + 1) == "TEXT" ) {
						if(PC == 0)
						{
							text_first = true;
							section_text = true;	
						}
						if(!section_text)
						{
							end_first_section = PC;
						}
						section_text = true;
						if (check_sessions > 1) {
							erros_list.push_back(erro_t(linha->nlinha,erros::SEMANTICO,erros::SECAO_REPETIDA)); 
						}
						check_sessions++;	
					} else if( *(token + 1) == "DATA" ) {
						if(!PC)
						{
							text_first = false;
							section_text = false;	
						}
						if(section_text)
						{
							end_first_section = PC;
						}
						section_text = false;	
						if (check_sessions > 1) {
							erros_list.push_back(erro_t(linha->nlinha,erros::SEMANTICO,erros::SECAO_REPETIDA)); 
						}
						check_sessions++;	
					} else {
						section_text = false;	
						erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO,erros::SECAO_INVALIDA)); 
						/*goto para terminar o montador caso seção não definida seja encontrada*/
						goto end_pass;
					}
				}
            }
//TOKEN é um símbolo qualquer (referência a labels)
            else if(isSymbol(*token))
            {

				/*Confere se o simbolo é uma instrução ou diretiva não definida*/
				bool inst_nao_def = false;
				string erro;
				if (has_label) {
					if (section_text) {
						erro = erros::COMP_INST_NAO_DEF;
					} else {
						erro = erros::COMP_DIR_NAO_DEF;
					}
					if (token - linha->tokens.begin() == 1) {
						erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO, erro)); 
						increment_add = 0;
						inst_nao_def = true;
					}
				} else {
					if (section_text) {
						erro = erros::COMP_INST_NAO_DEF;
					} else {
						erro = erros::COMP_DIR_NAO_DEF;
					}
					if (token - linha->tokens.begin() == 0) {
						erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO, erro)); 
						increment_add = 0;
						inst_nao_def = true;
					}
				}

                int i = symbol_exists(*token);

				/*If para evitar que a instrução não definida vá para o código objeto e zoe os erros*/
				if (!inst_nao_def) {
					/*Confere se a label ja existe e etc.*/
					if (i > -1)
					{
						if(simb_list[i].def)
						{
							obj_code.push_back(simb_list[i].value);
							if (*(token-1) == "COPY") {
								simb_list[i].lista_mem_changer.push_back(false);
							} else {
								simb_list[i].lista_mem_changer.push_back(last_inst_mem_changer);
							}
							simb_list[i].div_list.push_back(last_inst_div);
							simb_list[i].lista_nlinha.push_back(linha->nlinha);
						}
						else
						{
							simb_list[i].lista_end.push_back(PC);
							/*Lógica pro COPY e outras instruções não modificarem constante*/
							if (*(token-1) == "COPY") {
								simb_list[i].lista_mem_changer.push_back(false);
							} else {
								simb_list[i].lista_mem_changer.push_back(last_inst_mem_changer);
							}

							simb_list[i].div_list.push_back(last_inst_div);
							simb_list[i].lista_nlinha.push_back(linha->nlinha);
							obj_code.push_back(0);
						}
					}
					else
					{
						std::vector<int> index_list;
						index_list.push_back(PC);
						vector<bool> mem_changer_list;
						/*Lógica pro COPY e outras instruções não modificarem constante*/
						if (*(token-1) == "COPY") {
							mem_changer_list.push_back(0);
						} else {
							mem_changer_list.push_back(last_inst_mem_changer);
						}
						vector<bool> div_list;
						div_list.push_back(last_inst_div);
						vector<int> linha_list;
						linha_list.push_back(linha->nlinha);
						simb_list.push_back(smb_t((*token), -1, false, index_list,mem_changer_list,div_list,linha_list));
						obj_code.push_back(0);
					}
					mem_access_list.push_back(mem_acc_t(PC, last_inst_jmp, linha->nlinha));
				}

            }
//Se não for nenhum destes, é inválido
			else
			{
				erros_list.push_back(erro_t(linha->nlinha,erros::SINTATICO, erros::COMP_ARG_INV)); 
			}
            token++;
            PC+=increment_add; /**Nao pode contar diretivas**/
        }
        linha++;
    }


	if(check_sessions < 2) {
		erros_list.push_back(erro_t(0,erros::SEMANTICO, erros::SECAO_FALTANTE)); 
	}

end_pass:
    /*cout << "END FINAL : " << PC << endl;
    cout << "Nome, Valor, def, Lista de uso" << endl;
    for (int i = 0; i < (int) simb_list.size(); ++i)
    {
        cout << simb_list[i] << endl;
    }*/


	/* Adiciona os valores das labels definidas atrasado nos locais corretos de memória. */
    for(unsigned int i=0; i<simb_list.size(); i++)
    {
		for(unsigned int j=0; j < simb_list[i].lista_end.size(); j++)
        {
            if(simb_list[i].value  != -1)
            {
                obj_code[simb_list[i].lista_end[j]] += simb_list[i].value;
			}
        }
    }

	//Pega erros de acesso a labels por instrucoes erradas
	for (unsigned int i = 0; i < mem_access_list.size(); ++i)
	{
		if (text_first)
		{
			if (obj_code[mem_access_list[i].PC] > end_first_section-1)
			{
				if((unsigned int)obj_code[mem_access_list[i].PC] <= obj_code.size() ) {
					/*instrucao era jump*/
					if (mem_access_list[i].is_jump)
					{
						erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_JMP_ERRADO));
					}
				} else {
					erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_ACESSO_MEMORIA_INVALIDA));
				
				}
			} else if (obj_code[mem_access_list[i].PC] < 0 ) {
					erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_ACESSO_MEMORIA_INVALIDA));
			
			} else {
				if (!mem_access_list[i].is_jump)
				{
					erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_ACESSO_MEMORIA_INVALIDA));
				}
			}
		} else {
				if (obj_code[mem_access_list[i].PC] < end_first_section){
				/*instrucao era jump*/
					if (mem_access_list[i].is_jump)
					{
						erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_JMP_ERRADO));
					}
				} else if ((unsigned int)obj_code[mem_access_list[i].PC] > obj_code.size()) {
						erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_ACESSO_MEMORIA_INVALIDA));
				
				} else if (obj_code[mem_access_list[i].PC] < 0 ) {
						erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_ACESSO_MEMORIA_INVALIDA));
				
				} else {
					if (!mem_access_list[i].is_jump)
					{
						erros_list.push_back(erro_t(mem_access_list[i].linha,erros::SEMANTICO, erros::COMP_ACESSO_MEMORIA_INVALIDA));
					}
				}
		}
	}

	/* Grava os erros caso as labels terminem sem serem definidas*/
    for(unsigned int i=0; i<simb_list.size(); i++) {
		if(simb_list[i].value < 0) {
			for (unsigned int j = 0; j < simb_list[i].lista_nlinha.size(); j++) {
				erros_list.push_back(erro_t(simb_list[i].lista_nlinha[j],erros::SEMANTICO,erros::label_nao_def)); 
			}
		}
	}
	//Grava os erros de modificar memoria const e de divisao por zero
	for(unsigned int i = 0; i < simb_list.size(); i++)
	{
		if(simb_list[i].is_const)
		{
			int ok = symbol_exists(simb_list[i].simb);
			int valor_const = obj_code[(ok+simb_list.begin())->value];
			for(unsigned int j=0;j<simb_list[i].lista_mem_changer.size();j++)
			{
				if(simb_list[i].lista_mem_changer[j])
				{
					erros_list.push_back(erro_t(simb_list[i].lista_nlinha[j],erros::SEMANTICO,erros::mod_const));
				}
			}
			for(unsigned int j=0;j<simb_list[i].div_list.size();j++)
			{
			 	if(simb_list[i].div_list[j] && !valor_const)
				{
					erros_list.push_back(erro_t(simb_list[i].lista_nlinha[j],erros::SEMANTICO,erros::div_zero));
				}
			}
		}
	}

    //Soma os consts nos endereços que precisam
    for(unsigned int i=0; i<sum_list.size(); i++)
    {
        int ok = 0;
        /*Acha a posição do CONST na lista*/
        ok = symbol_exists(sum_list[i].simb);
        /*Se achou*/
        if(ok > -1)
        {
            /*O valor do símbolo é a posição na memória. Busca o valor desta posição*/
            int valor_const = obj_code[( ok + simb_list.begin())->value];
            obj_code[sum_list[i].position] += sum_list[i].signal*valor_const;
        }
    }

    //Mostra o codigo obj
    /*for(unsigned int i=0; i<obj_code.size(); i++)
    {
        cout << obj_code[i];
        if(i!=obj_code.size()-1)
        {
            cout << endl;
        }
    }*/
    return obj_code;
}

code_t PARSER::run_macros(code_t code)
{
    PARSER p;
    code = p.passagem_macros(code);
    return code;
}

vector<int> PARSER::run_montador(code_t code)
{
    PARSER p;
	vector<int> obj_code;
    obj_code = p.passagem_unica(code);
    return obj_code;
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

bool PARSER::isSymbol(string simb)
{
    string valid = "ABCDEFGHIJKLMNOPQRSTUVXYZ_0987654321";
    string beg_valid = valid.substr(0,26);
    int i = 0;
    if (beg_valid.find(simb[0]) ==  string::npos)
    {
        return false;
    }
    else
    {
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

bool PARSER::isNumber(string simb)
{
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
