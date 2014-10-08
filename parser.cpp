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
    bool erased = false;
    bool dlabel_inline = false;
    unsigned int c;
    vector<Linha>::iterator it = code.begin();
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
            //if(s == diretivas::END)
            //{
			  //erros.push_back(make_pair(_code[i].nlinha,"Erro sintatico, END sem uma macro"));
			  //i++;
			  //erased = false;
			  //dlabel_inline = false;
			  //continue;
		//}
		//checa se há dupla definicao de label na linha
		c=0;
		for(unsigned int j=0; j<_code[i].tokens.size() && c<2 ;j++)
		{
			  if(islabel(_code[i].tokens[j]))
			   {
				  //cout << _code[i].tokens[j];
				  //cin.get();
				    c++;
			  }
			  //cout << c;
		}
		if(c>1)
		{
		    dlabel_inline = true;
		}
		if(!dlabel_inline)
		{
		//Se a linha estiver correta coloca na lista de EQU a label
			  for(unsigned int j=0; j<_code[i].tokens.size(); j++)
			  {
				string aux(_code[i].tokens[j]);
				aux = aux.substr(0,aux.length()-1);
				if(islabel(_code[i].tokens[j]))
				{
					  if(_code[i].tokens[j+1] == diretivas::EQU)
					  {
						lista.push_back(make_pair(aux,atoi(_code[i].tokens[j+2].c_str())));
						_code.erase(_code.begin()+i);
						erased = true;
					  }
					  else
						    continue;
				}
				//cout << pch << endl;
			  }
		}
		else
		{
			  erros.push_back(make_pair(_code[i].nlinha,"Erro sintatico, redefinicao de label"));
			  i++;
			  dlabel_inline = false;
			  erased = false;
			  continue;
		}
            if(!erased)
		{
			  i++;
		}
            erased = false;
		dlabel_inline = false;
        }
//		for(unsigned int j=0;j<lista.size();j++)
//        {
//            cout << lista[j].first << ' ' << lista[j].second << endl;
//        }
//        EQU SECTION TEXT
        i=0;
        do
        {
            s.clear();
            memgetline(_code[i],s);
            i++;
        }
        while(s!=sections::S_TEXT && i<_code.size());
        erased = false;
        while(i<_code.size())
        {
            s.clear();
            memgetline(_code[i],s);
            if(s.find(diretivas::IF)!=string::npos)
            {
                for(unsigned int j=0; j<_code[i].tokens.size(); j++)
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
		{
			  i++;
		}
            erased = false;
        }
        //cout << s;
        //s.clear();
    }
    return _code;
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
