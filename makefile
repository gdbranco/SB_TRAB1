.phony: Opv.o prog

all: prog

prog: OpV.o
	g++ main.cpp OpV.o -o teste

OpV.o: OpV.h
	g++ -ansi -Wall OpV.cpp -c

clean:
	rm -f *.o
