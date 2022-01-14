#include "Parser.hpp"
#include <iostream>




Parser::Parser(){
    simbolos = {
        {0,{"PYC", ts_terminal, PYC}}
    };
}


Parser::Parser(){
    this->lexer = lexer;
    tokens();
}

Parser::~Parser(){
    
}

void Parser::programa()
{
    decalaraciones();
    sentencias();
    sedmantic.print();
    semantic.translate();
}

void Parser::declaraciones(){
    declaracion();
    declaraciones_();
}