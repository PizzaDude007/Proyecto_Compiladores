#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <stack>
#include <vector>
#include  <iostream>
using namespace std;
#include "Symbol.h"
#include "Production.h"
#include "Lexer.h"

class Parser{
    private:
        map <int, map<int,int>> table;
        map<int, Symbol> syms;
        vector<Production> prods;
        C_1::Lexer *lexer;
        int token;
        //table[i][j] = k;
    public:
        Parser(/*args*/);
        ~Parser();
        void loadSymbols();
        void loadProds();
        void loadTable();
        int parse();
};

#endif

