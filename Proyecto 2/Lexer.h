#ifndef LEXER_H
#define LEXER_H 

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h> 
//#include "tokens.h"
#endif


class Lexer: public yyFlexLexer
{
public:     
    Lexer(std::istream *in): yyFlexLexer(in){};
    Lexer();
    //~Lexer();
    using FlexLexer::yylex;
    virtual int yylex();
private:
    const int ERROR = -1;

};

/*
namespace C_1{
      class Scanner:public yyFlexLexer{
          public:
            Scanner(std:istream *in) : yyFlexLexer(in){};
            using FlexLexer::yylex;
            virtual int yylex();
          private:
            const int ERROR = -1;
      }
  }
*/

#endif 