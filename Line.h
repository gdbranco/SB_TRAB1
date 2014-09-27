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
    Line(){};
    Line(vector<string> _tokens,int _linha);
    int get_n_linha() const;
    vector<string> get_tokens() const;
    void set_n_Linha(const int& _linha);
    void set_Tokens(const vector<string>& _tokens);
};


inline int Line::get_n_linha() const
{
	return n_linha;
}

inline vector<string> Line::get_tokens() const
{
	return tokens;
}
#endif
