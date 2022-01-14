%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.h"
#include "Lexer.h"

%}

%option yyclass = "Lexer"
%option c++
%option outfile = "Lexer.cpp"
%option case-insensitive



ESP ([ \t\n\r])+
ID [a-zA-Z_]([a-zA-Z0-9_])*
ENTEROS ([0-9])+
FLOTANTES ([0-9])*(\.)([0-9])+([Ee]([+-])?([0-9])+)?f
CADENA (\")([\x20\x21\x23-\x7F])*(\")
CARACTER (\')([\x20\x21\x23-\x7F\t\n\r])(\')
DOBLES ([0-9])*(\.)([0-9])+([Ee]([+-])?([0-9])+)?
%%

"char" { return CHAR; }
"int" { return ENTERO; }
"float" { return FLOTANTE; }
"double" { return NUM_DOBLE; }
"struct" { return ESTRUCTURA; }
"id" { return IDENTIFICADOR; }
"{" { return LLAVE_IZQ; }
"}" { return LLAVE_DER; }
"(" { return PAR_IZQ; }
")" { return PAR_DER; }
"void" { return VACIO; }
"," { return COMA; }
"if" { return SI; }
"else" { return SINO; }
"while" { return MIENTRAS; }
"do" { return HACER; }
"=" { return IGUAL; }
"." { return PUNTO; }
"print" { return IMPRIME; }
";" { return PUNTO_COMA; }
"scan" { return ESCANER; }
"break" { return INTERRUMPE; }
"return" { return DEVUELVE; }
"+" { return MAS; }
"-" { return MENOS; }
"*" { return MULTIPLICACION; }
"/" { return DIVISION; }
"!=" { return DIFERENTE; }

"!" { return NEGACION}
"||" { return DISYUNCION; }
"&&" { return CONJUNCION; }
"<" { return MENOR; }
">" { return MAYOR; }
"==" {return IGUALDAD; }

">=" { return MAYOR_IGUAL; }
"<=" { return MENOR_IGUAL; }

{ID} { return IDENTIFICADOR; }
{ESP} {  }
{ENTEROS} { return NUMERO; }
{FLOTANTES} { return FLOTANTES; }
{DOBLES} { return DOBLES; }
{CADENA} { return CARACTERES; }
{CARACTER} { return CARACTER; }
.  { cout<<"ERROR LEXICO "<<yytext<<endl;}  

%%

int yyFlexLexer::yywrap(){
    return 1;
}