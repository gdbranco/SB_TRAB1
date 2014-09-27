#ifndef LINES_H
#define LINES_H
/*---------------------*/
#include<vector>
#include<string>
/*---------------------*/
using namespace std;
/*---------------------*/
class Line
{
private:
	int n_linha;
	vector<string> tokens;
public:

}


inline int Line::get_n_linha() const
{
	return n_linha;
}

inline vector<string> Line::get_tokens() const
{
	return tokens;
}
