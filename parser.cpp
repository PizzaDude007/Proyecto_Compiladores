#include "parser.h"
#include  <iostream>  


namespace C_1{

    Parser::Parser(/* args */){
        
    }
    Parser::Parser(Lexer *lexer){

        this->lexer = lexer;



        
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
        if(token == INT || token==FLOAT){
            declaracion();
            declaracionesP();
        }
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
            error("error tipo");    
            break;
        }
    }
    void Parser::lista_var(){
        
    }
    void Parser::lista_varP(){

    }
    void Parser::sentencias(){

    }
    void Parser::sentenciasP(){

    }
    void Parser::sentencia(){

    }
    void Parser::expresion(){

    }
    void Parser::expresionP(){

    }
    void Parser::termino(){

    }
    void Parser::terminoP(){

    }
    void Parser::factor(){

    }
    void Parser::eat(int t){

    }
    void Parser::error(string msg){
        
    }




} //HUevos Osvaldo













