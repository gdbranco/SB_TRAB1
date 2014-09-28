#ifndef OP_H
#define OP_H
#include "Basico.h"
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#define operadoresV "inst_diretiva.txt"
#define START_INST "START_INST"
#define END_INST "END_INST"
#define START_DIR "START_DIR"
#define END_DIR "END_DIR"
using namespace std;
typedef struct _inst
{
    int tamanho;
    string nome;
    int codigo;
    _inst(string _nome, int _codigo, int _tamanho)
    {
        tamanho = _tamanho;
        codigo  = _codigo;
        nome    = _nome;
    }
    friend ostream& operator<<(ostream& os, const _inst& it)
    {
        os << it.nome << ' ' << it.codigo << ' ' << it.tamanho;
        return os;
    }
}inst;
typedef struct _diretiva
{
    string nome;
    int operandos;
    int tamanho;
    _diretiva(string _nome, int _operandos, int _tamanho)
    {
        tamanho    = _tamanho;
        operandos  = _operandos;
        nome       = _nome;
    }
    friend ostream& operator<<(ostream& os, const _diretiva& it)
    {
        os << it.nome << ' ' << it.operandos << ' ' << it.tamanho;
        return os;
    }
}diretiva;
class Operador:public TipoBasico
{
private:
	void validar(string);
	static vector<inst> inst_validas;
	static vector<diretiva> diretivas_validas;
	void setInst_validas();
	void setDiretivas_validas();
public:
	Operador(){setInst_validas();setDiretivas_validas();};
	Operador(string);
	void showValidos();
	int pesquisar(string);
};
#endif
