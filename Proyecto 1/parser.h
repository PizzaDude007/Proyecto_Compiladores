#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include <string>
using namespace std;
#include "tokens.h"


namespace C_1{
    class Parser{
        private:
            Lexer *lexer;
            int token;
        public:
            Parser();
            Parser(Lexer *lexer);
            ~Parser();
            void programa();
            void declaraciones ();
            void declaracionesP();
            void declaracion();
            void tipo();
            void lista_var();
            void lista_varP();
            void sentencias();
            void sentenciasP();
            void sentencia();
            void expresion();
            void expresionP();
            void termino();          
            void terminoP();
            void factor();
            void eat(int t);
            void error(string msg);
            void parse();  //???
    };
}//name space


#endif
