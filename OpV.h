#ifndef ROTV_H
#define ROTV_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
#define operadoresV "operadoresValidos.txt"
class OpV
{
private:

public:
 	OpV(){setValidos();};
	void setValidos();
	void showValidos();
	int pesquisar(string);
	static vector<string> Validos;
};
#endif
