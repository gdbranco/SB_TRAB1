#include"Operador.h"
vector<inst> Operador::inst_validas;
vector<diretiva> Operador::diretivas_validas;
/***
Done: Lista de validacao
Todo: Operador atual, pesquisa na lista de validacao*/
Operador::Operador(string _op)
{
    setValor(_op);
}

void Operador::validar(string _op)
{
    throw invalid_argument("Operador/Diretiva invalidos.");
}
/************************************/
void Operador::setInst_validas()
{
    fstream outarq;
    outarq.open(operadoresV);
    string s;
    char *pch;
    vector<string> aux;
    do
    {
        getline(outarq,s);
    }
    while(s!=START_INST);
    while(getline(outarq,s))
    {
        if(!s.compare(END_INST))
            break;
        if(s.compare(""))
        {
            pch = strtok((char*)s.c_str(),"\t ");
            while(pch!=NULL)
            {
                aux.push_back(string(pch));
                pch = strtok(NULL,"\t ");
            }
            inst_validas.push_back(inst(aux.at(0),\
                                        atoi(aux.at(2).c_str()),\
                                        atoi(aux.at(3).c_str())));
            aux.clear();
        }
        else
            continue;
    }
    outarq.close();
}

void Operador::setDiretivas_validas()
{
    fstream outarq;
    outarq.open(operadoresV);
    string s;
    char *pch;
    vector<string> aux;
    do
    {
        getline(outarq,s);
    }
    while(s!=START_DIR);
    while(getline(outarq,s))
    {
        if(!s.compare(END_DIR))
            break;
        if(s.compare(""))
        {
            pch = strtok((char*)s.c_str(),"\t ");
            while(pch!=NULL)
            {
                aux.push_back(string(pch));
                pch = strtok(NULL,"\t ");
            }
            diretivas_validas.push_back(_diretiva(aux.at(0),\
                                        atoi(aux.at(1).c_str()),\
                                        atoi(aux.at(3).c_str())));
            aux.clear();
        }
        else
            continue;
    }
    outarq.close();
}

int Operador::pesquisar(string pesquisa)
{
    for(unsigned int i=0; i<inst_validas.size(); i++)
    {
        if(!pesquisa.compare(inst_validas.at(i).nome))
        {
            return 1;
        }
    }
    return 0;
}

void Operador::showValidos()
{
    cout << "-----INSTRUCOES VALIDAS-----\n";
    for(unsigned int i=0; i<inst_validas.size(); i++)
    {
        cout<< inst_validas.at(i) <<endl;
    }
    cout << "-----DIRETIVAS VALIDAS-----\n";
    for(unsigned int i=0;i<diretivas_validas.size();i++)
    {
        cout << diretivas_validas.at(i) << endl;
    }
}
