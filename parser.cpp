#include "parser.h"
vector<pair<int,string> > PARSER::erros;
string PARSER::retiraComentarios(string _linha)
{
    size_t found = _linha.find(';');
    if(found!=string::npos)
    {
//                cout << s << endl;
//                cout << found;
//                cin.get();
        _linha = _linha.substr(0,found-1);
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
        if(s!="")
        {
            s = retiraComentarios(s);
            pch = strtok((char*)s.c_str(),"\t ");
            while(pch!=NULL)
            {
                _tokens.push_back(string(pch));
//                cout << pch << endl;
                pch = strtok(NULL,"\t ");
            }
        }
        _linha++;
        memoria.push_back(Linha(_linha,_tokens));
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
    bool erased;
    vector<Linha> code = _code;
    vector<Linha>::iterator linha = code.begin();
    vector<string>::iterator token;
    vector<Define>::iterator define;
    if(!code.empty())
    {
        while(linha!=code.end())
        {
            erased = false;
            define = defines.begin();
            while(define!=defines.end())
            {
                //cout << define->label;
                //cout << define->label.length();
                //cout << define->label.substr(0,define->label.length()-1);
                //cin.get();
                /**Procura um label definido na linha**/
                if((find(linha->tokens.begin(),linha->tokens.end(),define->label.substr(0,define->label.length()-1))!=linha->tokens.end()))
                {
                    token = linha->tokens.begin();
                    /**Substitui os labels definidos na linha por seu valor EQU**/
                    while(token != linha->tokens.end())
                    {
                        stringstream ss;
                        ss << define->value;
                        if(*token == define->label.substr(0,define->label.length()-1))
                            *token = ss.str();
                        token++;
                    }
                    /**Checa se a linha eh um IF e se a proxima é valida**/
                    if((find(linha->tokens.begin(),linha->tokens.end(),diretivas::IF)!=linha->tokens.end()))
                    {
                        token = linha->tokens.begin();
                        while(token != linha->tokens.end())
                        {
                            if(*token == diretivas::IF)
                            {
                                token++;
                                if(*token == "0")
                                {
                                    //cout << *linha;
                                    //linha++;
                                    //cout << *(linha+1);
                                    code.erase(linha+1);
                                }
                                code.erase(linha);
                                erased = true;
                                /**Pensar noutra solucao depois**/
                                break;
                            }
                            token++;
                        }
                    }
                    //cout<< *linha<<endl;
                    //cin.get();
                }
                define++;
            }
            if(!erased)
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
    string s;
    if(!code.empty())
    {
        //Procura SECTION DATA
        while(linha!=code.end())
        {
            if((find(linha->tokens.begin(),linha->tokens.end(),sections::S) != linha->tokens.end()) \
                    && \
               (find(linha->tokens.begin(),linha->tokens.end(),sections::DATA) != linha->tokens.end()))
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
            token = linha->tokens.begin();
            while(token!=linha->tokens.end())
            {
                if(token->find(':')!=string::npos)
                {
                    string label = *token;
                    token++;
//                    cout << label << endl;
//                    cin.get();
                    if(token->find(diretivas::EQU)!=string::npos)
                    {
                        token++;
                        int value = atoi(token->c_str());
//                        cout << value;
                        Define _aux(label,value);
                        if(!define_exists(_aux))
                        {
                            defines.push_back(_aux);
                            code.erase(linha);
                            erased = true;
                        }
                        else
                        {
                            erros.push_back(make_pair(linha->nlinha,"Erro sintatico, Redefinicao de EQU"));
                        }
                        break;
                    }
                    else if(token->find(':')!=string::npos)
                    {
                        erros.push_back(make_pair(linha->nlinha,"Erro sintatico, duas labels na mesma linha"));
                        break;
                    }
                }
                else if(token->find(diretivas::EQU)!=string::npos)
                {
                    erros.push_back(make_pair(linha->nlinha,"Erro sintatico, EQU sem label"));
                    break;
                }
                token++;
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
        //vector<Define>::iterator it = defines.begin();
        //while(it!=defines.end())
        //{
        //cout << *it<< endl;
        //it++;
        //}

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
    if(!defines.empty())
    {
        define = defines.begin();
        while(define!=defines.end())
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
    size_t found;
    if((found = _label.find(':')!=string::npos) && _label[found+1] != '\0')
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
