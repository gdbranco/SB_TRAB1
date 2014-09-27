.phony: Operador.o prog

all: prog

prog: Operador.o
	g++ main.cpp Operador.o -o teste

Operador.o: Operador.h
	g++ -ansi -Wall Operador.cpp -c

clean:
	rm -f *.o
	rm -f teste
