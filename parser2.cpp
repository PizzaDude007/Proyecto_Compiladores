#include "parser.h"
#include  <iostream>    

namespace C_1{

    Parser::Parser(/* args */){
        
    }
    Parser::Parser(Lexer *lexer){

        this->lexer = lexer;
        
    }

    Parser::~Parser(){
        
    }
    
    void Parser::programa(){
        declaraciones();
        sentencias();            
    }
    void Parser::declaraciones (){
        declaracion();
        declaracionesP();
    }
    void Parser::declaracionesP(){
        while(token == INT || token==FLOAT){
            declaracion();
            //declaracionesP();
        } /* else {
            error("Se esperaba un token de tipo INT o FLOAT");
        } */
    }
    void Parser::declaracion(){
        tipo();
        lista_var();
    }
    void Parser::tipo(){
        switch (token)
        {
        case INT:
            eat(INT);
            break;
        case FLOAT:
            eat(FLOAT);
            break;
        default:
            error("El token debe ser INT o FLOAT");    
            break;
        }
    }
    void Parser::lista_var(){
        eat(ID);
        lista_varP();
    
    }
    void Parser::lista_varP(){
        while(token==COMA){
            eat(COMA);
            eat(ID);
            //lista_varP();            
        } /* else{
            error("Se esperaba un token de tipo COMA");
        } */

    }
    void Parser::sentencias(){
        sentencia();
        sentenciasP();
    }
    void Parser::sentenciasP(){
        while(token == ID | token == IF | token == WHILE){
            sentencia();
            //sentenciasP();
        }/* else{
            error("Se esperaba un token de tipo ID, IF o WHILE");
        } */
    }
    void Parser::sentencia(){

        switch (token)
        {
        case ID:
            eat(ID);
            eat(ASIG);
            expresion();
            eat(COMA);
            break;
        case IF:
            eat(IF);
            eat(RPAR);
            expresion();
            eat(LPAR);
            sentencias();
            eat(ELSE);
            sentencias();
            break;
        case WHILE:
            eat(WHILE);
            eat(RPAR);
            expresion();
            eat(LPAR);
            sentencias();
            break;
        default:
            error("Se esperaba un token de tipo ID, IF o WHILE");
            break;
        }        
    }
    void Parser::expresion(){
        termino();
        expresionP();
    }
    void Parser::expresionP(){

        while(token == MAS | token == MENOS){
            if (token == MAS) eat(MAS);//token = lexer->yylex();
            if (token == MENOS) eat(MENOS); //token = lexer->yylex();
            termino();
        }

        /* if(token==MAS){
            eat(MAS);
            termino();
            expresionP();
        }else if(token==MENOS){
            eat(MENOS);
            termino();
            expresionP();
        }else{
            error("Se esperaba un token de tipo MAS O MENOS");
        } */

    }
    void Parser::termino(){
        factor();
        terminoP();
    }
    void Parser::terminoP(){
        while(token == MUL | token == DIV){
            if (token == MUL) eat(MUL);//token = lexer->yylex();
            if (token == DIV) eat(DIV); //token = lexer->yylex();
            factor();
        }
    }


    void Parser::factor(){
        switch (token)
        {
        case LPAR:
            eat(LPAR);
            expresion();
            eat(RPAR);
            break;
        case ID:
            eat(ID);
            break;
        case ENTEROS:
            eat(ENTEROS);
            break;
        default:
            error("Se esperaba un token de tipo LPAR, ID o ENTEROS");
            break;
        }
    }
    void Parser::eat(int t){
        if(token == t){
            token = lexer->yylex();
        }else{
            error("Se esperaba el token"+lexer->token(token));
        }
    }
    void Parser::error(string msg){
        cout<<"ERROR de sintexis: "<<msg<<"en la linea"/*<<lexer->getLine()*/<<endl;
        exit(-1);
    }

    void Parser::parse(){
        token = lexer->yylex();
        programa();
        if (token == 0){
            cout << "La cadena es aceptada"<<endl;
        }else{
            cout<<"La cadena no pertenece al lenguaje"<<endl;
        }
    }

} 