#include "parser.h"
vector<Erro> PARSER::erros_list;
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
vector<Linha> PARSER::toMEM(string nome)
{
    vector<Linha> memoria;
    vector<string> _tokens;
    int _linha=0;
    fstream sc;
    char* pch;
    sc.open(nome.c_str());
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
                _tokens.push_back(string(pch));
//                cout << pch << endl;
                pch = strtok(NULL,"\t ");
            }
            memoria.push_back(Linha(_linha,_tokens));
        }
        _tokens.clear();
    }
    sc.close();
    return memoria;
}
void PARSER::memgetline(const Linha _code, string &s)
{
    s.clear();
    for(unsigned int j=0; j<_code.tokens.size(); j++)
    {
        s.append(_code.tokens[j]);
        s.append(" ");
    }
    s.erase(s.length()-1);
}
vector<Linha> PARSER::run_preproc(vector<Linha> _code)
{
    bool erase_currentline;
    bool erase_nextline;
    bool erro;
    bool achei;
    vector<Linha> code = _code;
    vector<Linha>::iterator linha = code.begin();
    vector<string>::iterator token;
    vector<Define>::iterator define;
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
            /**Procura um label definido na linha**/
//            token = linha->tokens.begin();
//                /**Substitui os labels definidos na linha por seu valor EQU**/
//                while(token != linha->tokens.end())
//                {
//                    define = defines_list.begin();
//                    while(define!=defines_list.end())
//                    {
//                        stringstream ss;
//                        ss << define->value;
//                        if(*token == define->label.substr(0,define->label.length()-1))
//                            *token = ss.str();
//                        define++;
//                    }
//                    token++;
//                }
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
                    erros_list.push_back(Erro(linha->nlinha,erros::SEMANTICO,erros::EQU_ndefinida));
                }
                token = linha->tokens.begin();
                /**Se nao houver linhas faz a avaliacao do IF**/
                while(token != linha->tokens.end() && !erro)
                {
//                    cout << *token;
//                    cin.get();
                    if(*token == diretivas::IF)
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
            //cout<< *linha<<endl;
            //cin.get();
            if(!erase_currentline)
                linha++;
        }
    }
    return code;
}
vector<Linha> PARSER::make_listaEQU(vector<Linha> _code)
{
    vector<Linha> code = _code;
    vector<Linha>::iterator linha = code.begin();
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
                        Define _aux(label,value);
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
                erros_list.push_back(Erro(linha->nlinha,erros::SINTATICO,erros::label_redefinida));
                break;
            case 2:
                erros_list.push_back(Erro(linha->nlinha,erros::SINTATICO,erros::label_dupla));
                break;
            case 3:
                erros_list.push_back(Erro(linha->nlinha,erros::SINTATICO,erros::EQU_nlabeled));
                break;
            default:
                //Sem erros
                break;
            }
//            unsigned int i=0;
//            while(i<linha->tokens.size())
//            {
//                cout << linha->tokens[i];
//                i++;
//            }
            if(!erased)
                linha++;
        }
        /**Mostrando o vetor para testes**/
        vector<Define>::iterator it = defines_list.begin();
//        while(it!=defines_list.end())
//        {
//            cout << *it<< endl;
//            it++;
//        }

    }
    return code;
}
vector<Linha> PARSER::pre_proc(vector<Linha> code)
{
    PARSER p;
    code = p.make_listaEQU(code);
    code = p.run_preproc(code);
    return code;
}

int PARSER::define_exists(Define procura)
{
    vector<Define>::iterator define;
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
    if(_dir == diretivas::SECTION)
        return 1;
    else if(_dir == diretivas::TEXT)
        return 1;
    else if(_dir == diretivas::DATA)
        return 1;
    else if(_dir == diretivas::SPACE)
        return 1;
    else if(_dir == diretivas::IF)
        return 1;
    else if(_dir == diretivas::EQU)
        return 1;
    else if(_dir == diretivas::END)
        return 1;
    else if(_dir == diretivas::CONST)
        return 1;
    else if(_dir == diretivas::MACRO)
        return 1;
    return !OK;
}
//retorno = (inst valida) ? inst.opcode : 1
int PARSER::isinst(string _inst)
{
    if(_inst == instructions::ADD.first)
    {
        return instructions::ADD.second;
    }
    else if(_inst == instructions::SUB.first)
    {
        return instructions::SUB.second;
    }
    else if(_inst == instructions::MULT.first)
    {
        return instructions::MULT.second;
    }
    else if(_inst == instructions::DIV.first)
    {
        return instructions::DIV.second;
    }
    else if(_inst == instructions::JMP.first)
    {
        return instructions::JMP.second;
    }
    else if(_inst == instructions::JMPN.first)
    {
        return instructions::JMPN.second;
    }
    else if(_inst == instructions::JMPP.first)
    {
        return instructions::JMPP.second;
    }
    else if(_inst == instructions::JMPZ.first)
    {
        return instructions::JMPZ.second;
    }
    else if(_inst == instructions::COPY.first)
    {
        return instructions::COPY.second;
    }
    else if(_inst == instructions::LOAD.first)
    {
        return instructions::LOAD.second;
    }
    else if(_inst == instructions::STORE.first)
    {
        return instructions::STORE.second;
    }
    else if(_inst == instructions::INPUT.first)
    {
        return instructions::INPUT.second;
    }
    else if(_inst == instructions::OUTPUT.first)
    {
        return instructions::OUTPUT.second;
    }
    else if(_inst == instructions::STOP.first)
    {
        return instructions::STOP.second;
    }
    return !OK;
}
