all: macro_run

macro_run: macros Macro MacroTable defines parser teste
	g++ -g -std=c++11 Macro.o MacroTable.o macros.o teste.o defines.o parser.o -o a.out

macros: macros.cpp
	g++ -g -std=c++11 -ansi -Wall macros.cpp -c 

Macro: Macro.cpp
	g++ -g -std=c++11 -ansi -Wall Macro.cpp -c 

MacroTable: MacroTable.cpp
	g++ -g -std=c++11 -ansi -Wall MacroTable.cpp -c

defines: defines.cpp
	g++ -g -std=c++11 -ansi -Wall defines.cpp -c 

parser: parser.cpp
	g++ -g -std=c++11 -ansi -Wall parser.cpp -c 

teste: teste.cpp
	g++ -g -std=c++11 -ansi -Wall teste.cpp -c

clean:
	rm -rf *.o
