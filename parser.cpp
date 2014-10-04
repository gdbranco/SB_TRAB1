#include "parser.h"
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
    for(unsigned int j=0; j<_code.tokens.size(); j++)
    {
        s.append(_code.tokens[j]);
        s.append(" ");
    }
    s.erase(s.length()-1);
}
vector<Linha> PARSER::pre_proc(vector<Linha> code)
{
    unsigned int i = 0;
    vector<pair<string,int> > lista;
    vector<Linha> _code = code;
    if(!_code.empty())
    {
        string s;
        do
        {
            s.clear();
            memgetline(_code[i],s);
            i++;
        }
        while(s!=sections::S_DATA && i<_code.size());
        while(i<_code.size())
        {
            s.clear();
            memgetline(_code[i], s);
            if(s == diretivas::END)
                break;
            for(unsigned int j=0; j<_code[i].tokens.size(); j++)
            {
//                if(j+1>_code[i].tokens.size() || j+2>_code[i].tokens.size())
//                    continue;
                string aux(_code[i].tokens[j]);
                aux = aux.substr(0,aux.length()-1);
                if(islabel(_code[i].tokens[j]) && _code[i].tokens[++j] == diretivas::EQU)
                {
                    lista.push_back(make_pair(aux,atoi(_code[i].tokens[++j].c_str())));
                }
                //cout << pch << endl;
            }
            i++;
        }
//		for(unsigned int j=0;j<lista.size();j++)
//        {
//            cout << lista[j].first << ' ' << lista[j].second << endl;
//        }
        i=0;
        do
        {
            s.clear();
            memgetline(_code[i],s);
            i++;
        }
        while(s!=sections::S_TEXT && i<_code.size());
        bool erased = false;
        while(i<_code.size())
        {
            s.clear();
            memgetline(_code[i],s);
//            cout << s;
//            cin.get();
            size_t found = s.find(';');
            if(found!=string::npos)
            {
//                cout << s << endl;
//                cout << found;
//                cin.get();
                s = s.substr(0,found-1);
            }
            if(s.find(diretivas::EQU)!=string::npos)
            {
                _code.erase(_code.begin()+i);
                erased = true;
            }
            else if(s.find(diretivas::IF)!=string::npos)
            {
                for(unsigned int j=0;j<_code[i].tokens.size();j++)
                {
                    if(diretivas::IF == _code[i].tokens[j])
                    {
                        j++;
                        for(unsigned int k=0; k<lista.size(); k++)
                        {
                            if((lista[k].first == _code[i].tokens[j]) && !lista[k].second)
                            {
                                _code.erase(_code.begin()+i+1);
                            }
                        }
                    }
                }
                _code.erase(_code.begin()+i);
                erased = true;
            }
//            cout << i;
//            cin.get();
            if(!erased)
                i++;
            erased = false;
        }
        //cout << s;
        //s.clear();
    }
    return _code;
}
void PARSER::pre_proc(string _arquivo)
{
    fstream arq;
    arq.open(_arquivo.c_str());
    bool DATA_FIRST=true;
    int linha = 0;
    string s;
    vector<pair<string,int> > lista;
    char *pch;
    if(arq)
    {
        do
        {
            getline(arq,s);
            linha++;
        }
        while(s!=sections::S_DATA);
        if(linha>1)
        {
//            cout << linha;
//            cin.get();
            DATA_FIRST = false;
        }
        if(DATA_FIRST)
            cout << s << endl;
        while(getline(arq,s))
        {
            if(DATA_FIRST)
                cout << s << endl;
            if(s == diretivas::END)
                break;
            if(s != "")
            {
                pch = strtok((char*)s.c_str(),"\t ");
                while(pch!=NULL)
                {
                    string aux(pch);
                    aux = aux.substr(0,aux.length()-1);
                    if(islabel(string(pch)) && string(pch = strtok(NULL,"\t ")) == diretivas::EQU) //!strcmp((pch = strtok(NULL,"\t ")),diretivas::EQU.c_str())
                    {
                        lista.push_back(make_pair(aux,atoi(pch=strtok(NULL,"\t "))));
                    }
                    //cout << pch << endl;
                    pch = strtok(NULL,"\t ");
                }
            }
        }
        arq.clear();
        arq.seekg(0,arq.beg);
        do
        {
            getline(arq,s);
        }
        while(s!=sections::S_TEXT);
        cout << s << endl;
        int nextline = 1;
        while(getline(arq,s))
        {
            size_t found = s.find(';');
            if((found!=string::npos))
            {
//                cout << s << endl;
//                cout << found;
//                cin.get();
                s = s.substr(0,found-1);
            }
            //(s.find(diretivas::EQU)==string::npos) xor
            if(((s.find(diretivas::EQU)==string::npos) and (s.find(diretivas::IF)==string::npos)) xor !nextline)
            {
                cout << s << endl;
            }
            nextline = 1;
            if(s == diretivas::END && DATA_FIRST)
                break;
            if(s != "")
            {
                pch = strtok((char*)s.c_str(),"\t ");
                while(pch!=NULL)
                {
                    string aux(pch);
                    //cout << pch << endl;
                    if(!strcmp(pch,diretivas::IF.c_str()))
                    {
                        pch = strtok(NULL,"\t ");
                        for(unsigned int i=0; i<lista.size(); i++)
                        {
                            if((!strcmp(pch,lista[i].first.c_str()) && !lista[i].second)||(!atoi(pch)))
                            {
                                nextline = 0;
                            }
                        }
                    }
                    pch = strtok(NULL,"\t ");
                }
            }
        }
        arq.close();
    }
}

int PARSER::islabel(string _label)
{
    size_t found;
    if((found = _label.find(':')!=string::npos) && _label[found+1] != '\0')
        return OK;
    return -OK;
}

int PARSER::iscomment(string _comment)
{
    size_t found;
    if((found = _comment.find(';')!=string::npos))
        return OK;
    return -OK;
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
    return -1;
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
    return -1;
}
