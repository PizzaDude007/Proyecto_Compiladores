#include "Parser.h"

/*
0 programa→ declaraciones sentencias
1 declaraciones → declaración declaraciones’
2 declaraciones’ → declaración declaraciones’ | 𝜀
3 declaración → tipo lista-var ;
4 tipo → int | float
5 lista-var → identificador lista-var’
6 lista-var’ → , identificador lista-var’ | 𝜀
7 sentencias → sentencia sentencias’
8 sentencias’ → sentencia sentencias’ | 𝜀
9 sentencia→ identificador = expresión ;
            | if (expresión) sentencias else sentencias  
            | while(expresión) sentencias
10 expresión → término expresión’
11 expresión’ → + término expresión’ | - término expresión’| 𝜀
12 término → factor término’
13 término' → * factor término’| / factor término’| 𝜀
14 factor → ( expresión )| identificador| número

/*
const int $ = 0; 
const int MAS = 1;
const int MENOS = 2;
const int MUL = 3;
const int DIV = 4;
const int ASIG = 5;
const int LPAR = 6;
const int RPAR = 7;
const int PYC = 8;
const int COMA = 9;
const int ENTEROS = 10;
const int FLOTANTES = 19;
const int INT = 24;
const int FLOAT = 28;
const int ELSE = 31;
const int IF = 18;
const int WHILE = 35;
const int ID = 16;
const int ESP = 17;
*/

void Parser::loadSymbols(){
    syms[0] = Symbol("programa", noterminal,0);
    syms[1] = Symbol("declaraciones", noterminal,1);
    syms[2] = Symbol("declaracionesP", noterminal,2);
    syms[3] = Symbol("declaracion", noterminal,3);
    syms[4] = Symbol("tipo", noterminal,4);
    syms[5] = Symbol("lista-var", noterminal,5);
    syms[6] = Symbol("lista-varP", noterminal,6);
    syms[7] = Symbol("sentencias", noterminal,7);
    syms[8] = Symbol("sentenciasP", noterminal,8);
    syms[9] = Symbol("sentencia", noterminal,9);
    syms[10] = Symbol("expresion", noterminal,10);
    syms[11] = Symbol("expresionP", noterminal ,11);
    syms[12] = Symbol("termino", noterminal ,12);
    syms[13] = Symbol("terminoP", noterminal ,13);
    syms[14] = Symbol("factor", noterminal ,14);
    syms[15] = Symbol("$", terminal ,0);
    syms[16] = Symbol("MAS", terminal ,1);
    syms[17] = Symbol("MENOS", terminal ,2);
    syms[18] = Symbol("MUL", terminal ,3);
    syms[19] = Symbol("DIV", terminal ,4);
    syms[20] = Symbol("ASIG", terminal ,5);
    syms[21] = Symbol("LPAR", terminal ,6);
    syms[22] = Symbol("RPAR", terminal ,7);
    syms[23] = Symbol("PYC", terminal ,8);
    syms[24] = Symbol("COMA", terminal ,9);
    syms[25] = Symbol("ENTEROS", terminal ,10);
    syms[26] = Symbol("FLOTANTES", terminal ,19);
    syms[27] = Symbol("INT", terminal ,24);
    syms[28] = Symbol("FLOAT", terminal ,28);
    syms[29] = Symbol("ELSE", terminal ,31);
    syms[30] = Symbol("IF", terminal ,18);
    syms[31] = Symbol("WHILE", terminal ,35);
    syms[32] = Symbol("ID", terminal ,16);
    syms[33] = Symbol("EPS", terminal ,17);
    syms[34] = Symbol("ESP", cadena ,0);
}
/*
0 programa→ declaraciones sentencias
1 declaraciones → declaración declaraciones’
2 declaraciones’ → declaración declaraciones’ | 𝜀
3 declaración → tipo lista-var ;
4 tipo → int | float
5 lista-var → identificador lista-var’
6 lista-var’ → , identificador lista-var’ | 𝜀
7 sentencias → sentencia sentencias’
8 sentencias’ → sentencia sentencias’ | 𝜀
9 sentencia→ identificador = expresión ;
            | if (expresión) sentencias else sentencias  
            | while(expresión) sentencias
10 expresión → término expresión’
11 expresión’ → + término expresión’ | - término expresión’| 𝜀
12 término → factor término’
13 término' → * factor término’| / factor término’| 𝜀
14 factor → ( expresión )| identificador| número
*/

void Parser::loadProds(){
    vector<int> s = {1,7};
    prods[0] = Production(0, s);
    s.clear();
    s = {3,2};
    prods[1] = Production(1, s);
    s.clear();
    s = {3, 2};
    prods[2] = Production(2, s);
    s.clear();
    s = {33};
    prods[3] = Production(2, s);
    s.clear();
    s = {4,5,23};
    prods[4] = Production(3, s);
    s.clear();
    s = {27};
    prods[5] = Production(4, s);
    s.clear();
    s = {28};
    prods[6] = Production(4, s);
    s.clear();
    s = {32,6};
    prods[7] = Production(5, s);
    s.clear();
    s = {24,32,6};
    prods[8] = Production(6, s);
    s.clear();
    s = {33};
    prods[9] = Production(6, s);
    s.clear();
    s = {9,8};
    prods[10] = Production(7, s);
    s.clear();
    s = {9,8};
    prods[11] = Production(8, s);
    s.clear();
    s = {33};
    prods[12] = Production(8, s);
    s.clear();
    s = {32,20,10,23};
    prods[13] = Production(9, s);
    s.clear();
    s = {30,21,10,22,7,29,7};
    prods[14] = Production(9, s);
    s.clear();
    s = {31,21,10,22,7};
    prods[15] = Production(9, s);
    s.clear();
    s = {12,11};
    prods[16] = Production(10, s);
    s.clear();
    s = {16,12,11};
    prods[17] = Production(11, s);
    s.clear();
    s = {17,12,11};
    prods[18] = Production(11, s);
    s.clear();
    s = {33};
    prods[19] = Production(11, s);
    s.clear();
    s = {14,13};
    prods[20] = Production(12, s);
    s.clear();
    s = {18,14,13};
    prods[21] = Production(13, s);
    s.clear();
    s = {19,14,13};
    prods[22] = Production(13, s);
    s.clear();
    s = {33};
    prods[23] = Production(13, s);
    s.clear();
    s = {21,10,22};
    prods[24] = Production(14, s);
    s.clear();
    s = {32};
    prods[25] = Production(14, s);
    s.clear();
    s = {25};
    prods[26] = Production(14, s);
    s.clear();
        
}

/*
0 programa→ declaraciones sentencias
1 declaraciones → declaración declaraciones’
2 declaraciones’ → declaración declaraciones’ | 𝜀
3 declaración → tipo lista-var ;
4 tipo → int | float
5 lista-var → identificador lista-var’
6 lista-var’ → , identificador lista-var’ | 𝜀
7 sentencias → sentencia sentencias’
8 sentencias’ → sentencia sentencias’ | 𝜀
9 sentencia→ identificador = expresión ;
            | if (expresión) sentencias else sentencias  
            | while(expresión) sentencias
10 expresión → término expresión’
11 expresión’ → + término expresión’ | - término expresión’| 𝜀
12 término → factor término’
13 término' → * factor término’| / factor término’| 𝜀
14 factor → ( expresión )| identificador| número
*/

void Parser::loadTable(){
    table[0][24] = 0;
    table[0][28] = 0;
    
    table[1][24] = 1;
    table[1][28] = 1;

    table[2][24] = 2;
    table[2][28] = 2;
    table[2][16] = 3;
    table[2][18] = 3;
    table[2][35] = 3;
    
    table[3][24] = 4;
    table[3][28] = 4;
    
    table[4][24] = 5;
    table[4][28] = 6;

    table[5][16] = 7;
    
    table[6][9] = 8;
    table[6][8] = 9;
        
    table[7][16] = 10;
    table[7][18] = 10;
    table[7][35] = 10;
    
    table[8][16] = 11;
    table[8][18] = 11;
    table[8][35] = 11;
    //table[8][18] = 12; // Se sobreescribe ? OuO?
    //table[8][35] = 12;
    //table[8][16] = 12;
    table[8][0] = 12;
    table[8][31] = 12;
    
    table[9][16] = 13;
    table[9][18] = 14;
    table[9][35] = 15;
    
    table[10][6] = 16;
    table[10][16] = 16;
    table[10][10] = 16;
    
    table[11][1] = 17;
    table[11][2] = 18;
    table[11][8] = 19;
    table[11][7] = 19;
    
    table[12][6] = 20;
    table[12][16] = 20;
    table[12][10] = 20;

    table[13][3] = 21;
    table[13][4] = 22;
    table[13][1] = 23;
    table[13][2] = 23;
    table[13][8] = 23;
    table[13][7] = 23;
    
    table[14][6] = 24;
    table[14][16] = 25;
    table[14][10] = 26;
}

int Parser::parse(){
    stack<Symbol> pila;
    
    token = lexer->yylex();
    pila.push(syms[15]);
    pila.push(syms[0]);
    cout<<pila.top().getName()<<endl;
    while (pila.top().getName()!="$")
    {

        if (pila.top().getName() == lexer->getYytext()){

        }else if(pila.top().getType() == terminal){


        }else if (pila.top().getType() == noterminal ){

            
        }
    }
}
 
    
