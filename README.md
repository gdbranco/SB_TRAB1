Montador
========

Projeto de montador para a disciplina de Software Básico.

Instruções de compilação
------------------------

O código deve ser compilado com o Makefile na pasta principal.  
As flags utilizadas são:  

`CFLAGS = -ansi -Wall -c`  

A opção **make clean** pode ser usada para remover os arquivos de saída do montador.  

Instruções de execução
----------------------

O programa recebe dois argumentos obrigatórios e um opcional, nessa ordem:  

- A flag de compilação.

  1. O programa pode fazer apenas o pré-processamento (-p), retirando comentários e espaços em branco, e substituindo EQU e IFs.
  2. Pode realizar o pré-processamento e a passagem de macros, substituindo as definições de macros pelo seu corpo.
  3. Compilação completa, gerando código objeto.  

- O arquivo de input, sem extensão.  
- Um arquivo opcional, de saída, também sem extensão.  

Exemplo de uso:

`./montador -o arquivo_de_input arq_saida`


Visão geral do projeto
----------------------

O código se divide essencialmente em 4 arquivos, com seus headers:  

- defines.cpp
- MacroTable.cpp
- parser.cpp 
- main.cpp


###defines
No arquivo defines.h se encontram todas as declarações das classes e typedefs usados no programa, como a struct referente a cada símbolo da Tabela de Símbolos, a definição da struct de linha, o namespace das instruções, entre outros.  
No defines.cpp se encontram as implementações de alguns tipos, como mensagens de erro, tamanho das instruções e etc.

A única classe definida fora deste arquivo é a da tabela de macros, que possui alguns métodos específicos.


###MacroTable
Nos arquivos MacroTable.h e MacroTable.h se encontram as declarações e implementações, respectivamente, das funções que realizam as partes específicas da passagem de macros, como checar se uma macro existe na tabela de definições e retornar o corpo de uma macro já definida.
Todos as funções destes arquivos são métodos da classe **MacroTable**, definida no MacroTable.h.

###parser
São nesses arquivos que se encontram a parte central do montador, incluindo leitura do código-fonte, o pré-processamento e a passagem para geração de código objeto.  
É no parser.cpp que se localizam as principais do programa, como a lista de erros encontrados e a tabela de símbolos.  
Funções utilitárias também se encontram nele, como isNumber, isLabel, função para ler do arquivo de input para memória.  
As funções de cada passagem em si são privadas, mas abstraídas por funções públicas para serem acessadas pela main.

###main
Arquivo de interface com o usuário (recebimento de parâmetros por linha de comando) e chamada das funções do parser.cpp. 


Autores
-------
* Guilherme David Branco	-	11/0012470
* Lucas de Moura Amaral 	-	11/0015690

