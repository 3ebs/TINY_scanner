#ifndef __TINY_SCANNER__
#define __TINY_SCANNER__

#include <fstream>
#include <string>
#include <list>
#include <regex>
#include <iostream>

#define num_of_ss   10
#define num_of_rw   8
#define index_of_RW 10

using namespace std;

enum
{
    PLUS, MINUS, MULTIPLY, DIVISION, EQUAL, LESS, PARENTHESE_OPEN, PARENTHESE_CLOSE, SEMI, GREATER,\
    IF, THEN, ELSE, END, REPEAT, UNTIL, READ, WRITE,\
    ASSIGN, LESS_OR_EQUAL, GREATER_OR_EQUAL, NUM, ID
};

typedef struct
{
    int tokentype;
    string stringValue;
}TokenRecord;

typedef struct
{
	int index;
	int value;
}ReservedWord;

class Scanner
{
    private:
        list<TokenRecord> tokenlist;
		list<ReservedWord> RW;
        ifstream file;
        ofstream outFile;
        unsigned char specialSymbols[num_of_ss] = {'+', '-', '*', '/', '=', '<', '(', ')', ';', '>'};
        string reservedWords[num_of_rw+3] = {"if", "then", "else", "end", "repeat", "until", "read", "write", ":=", "<=", ">="};
		string tokens[num_of_rw + num_of_ss + 5] = {"PLUS", "MINUS", "MULTIPLY", "DIVISION", "EQUAL", "LESS", "PARENTHESIS_OPEN", "PARENTHESIS_CLOSE", "SEMI", "GREATER",\
													"IF", "THEN", "ELSE", "END", "REPEAT", "UNTIL", "READ", "WRITE",\
													"ASSIGN", "LESS_OR_EQUAL", "GREATER_OR_EQUAL", "NUM", "ID" };
		bool scanSpecialSymbols(unsigned char x, string & y);
		int scanReservedWords(string x, string y);
		void getTokens(void);
    public:
        Scanner(string f);
        void getTokenTable(void);
};


#endif /*__TINY_SCANNER__*/
