#ifndef LEXER_H
#define LEXER_H
#include <fstream>
#include <string>
using namespace std;

namespace C_1{
    class Lexer{
        private:
            const int ERROR = -1;
            const int ACEPTAR = 0;
            /*const int MAS = 1;
            const int MENOS = 2;
            const int MUL = 3;
            const int DIV = 4;
            const int ID = 5;*/
            // TODO(8) Completar las constantes que faltan de los tokens
            ifstream yyin;
            int transiciones[36][26];
            bool *acc;
            int last;
            string yytext; //Buffer de lo que estamos leyendo
            int yyline; //Contador de lineas
            char c; // caracter para ir leyendo
        public:
            Lexer(string file);
            ~Lexer();
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            bool readAFD(string file);
            void getChar();
            bool openFile(string file);
            void closeFile();
            int yylex(); // Regresa tokens
            int charToColumn(char c);
            int token(int q);
            string getYytext();
    };

  
};
#endif



/*
#ifndef LEXER_H
#define LEXER_H
#include <fstream>
#include <string>
using namespace std;

namespace C_1{    

    class Lexer
    {
    private:        
        const int ERROR = -1;
        const int ACEPTAR = 0;
        const int MAS = 1;
        const int MENOS = 2;
        const int MUL = 3;
        const int DIV = 4;
        const int ID = 5;
        // TODO(8) Completar las constantes que faltan de los tokens
        ifstream yyin;
        int **transiciones;
        bool *acc;        
        string yytext;
        int yyline;
        char c;

    public:
        Lexer( args );
        ~Lexer();

        bool readAFD(string file);
        char getChar();
        bool openFile(string file);
        int yylex();
        int charToColumn(char c);
        int token(int q);
        string getYytext();    
    };  
    
    
}

#endif
*/