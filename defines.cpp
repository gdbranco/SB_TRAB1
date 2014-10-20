#include "defines.h"
namespace run_type
{
    string PRE_PROCESS_EQU = "-p";
    string PRE_PROCESS_MACRO = "-m";
    string COMPILE = "-o";
}
namespace erros
{
    string SINTATICO                    = "ERRO SINTATICO";
    string SEMANTICO                    = "ERRO SEMANTICO";
    string LEXICO                       = "ERRO LEXICO";
    string label_redefinida             = "Redefinicao de label";
    string label_dupla                  = "Duas labels na mesma linha";
    string label_nao_def                = "Label não definida";
    string EQU_nlabeled                 = "EQU sem label";
    string EQU_ndefinida                = "EQU nao definido";
    string MACRO_no_label               = "Macro não pode ser definida sem label";
    string MACRO_label_no_delimiter     = "Label da macro precisa terminar em ':'";
    string MACRO_endless                = "Macro sem delimitação final";
    string COMP_COPY_VIRGULA            = "Copy sem vírgula";
    string COMP_EXPR_INCORRETA          = "Expressão (soma/subtração) malformada";
	string COMP_QTD_OPERANDOS_INV       = "Quantidade de operandos inválida";
	string COMP_INST_SECAO_ERRADA       = "Instrução na seção de dados";
	string COMP_DIR_SECAO_ERRADA        = "Diretiva na seção de dados";
	string COMP_INST_NAO_DEF            = "Instrução não definida";
	string COMP_DIR_NAO_DEF             = "Diretiva não definida";
	string COMP_ARG_INV                 = "Argumento inválido";
	string COMP_JMP_ERRADO              = "Jump para secao de dados";
	string COMP_ACESSO_MEMORIA_INVALIDA = "Acessando memoria em local indevido";
	string SECAO_FALTANTE               = "Seção faltante";
	string SECAO_INVALIDA               = "Seção inválida";
	string SECAO_REPETIDA               = "Seção repetida";
	string mod_const                    = "Nao se pode modificar uma constante";
	string div_zero                     = "Divisao por zero";
}
namespace instructions
{
    unsigned int tamanhoGeral = 2;
    unsigned int tamanhoCOPY  = 3;
    unsigned int tamanhoSTOP  = 1;
    inst_t ADD    = inst_t("ADD",1,tamanhoGeral,tamanhoGeral-1);
    inst_t SUB    = inst_t("SUB",2,tamanhoGeral,tamanhoGeral-1);
    inst_t MULT   = inst_t("MULT",3,tamanhoGeral,tamanhoGeral-1);
    inst_t DIV    = inst_t("DIV",4,tamanhoGeral,tamanhoGeral-1);
    inst_t JMP    = inst_t("JMP",5,tamanhoGeral,tamanhoGeral-1);
    inst_t JMPN   = inst_t("JMPN",6,tamanhoGeral,tamanhoGeral-1);
    inst_t JMPP   = inst_t("JMPP",7,tamanhoGeral,tamanhoGeral-1);
    inst_t JMPZ   = inst_t("JMPZ",8,tamanhoGeral,tamanhoGeral-1);
    inst_t COPY   = inst_t("COPY",9,tamanhoCOPY,tamanhoCOPY-1);
    inst_t LOAD   = inst_t("LOAD",10,tamanhoGeral,tamanhoGeral-1);
    inst_t STORE  = inst_t("STORE",11,tamanhoGeral,tamanhoGeral-1);
    inst_t INPUT  = inst_t("INPUT",12,tamanhoGeral,tamanhoGeral-1);
    inst_t OUTPUT = inst_t("OUTPUT",13,tamanhoGeral,tamanhoGeral-1);
    inst_t STOP   = inst_t("STOP",14,tamanhoSTOP,tamanhoSTOP-1);
}
namespace diretivas
{
    string TEXT    = "TEXT";
    string DATA    = "DATA";
    string SECTION = "SECTION";
    string SPACE   = "SPACE";
    string CONST   = "CONST";
    string EQU     = "EQU";
    string IF      = "IF";
    string MACRO   = "MACRO";
    string END     = "END";
}
