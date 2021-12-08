#include "Lexer.h"
#include "tokens.h"

#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <sstream>
#include<fstream>

namespace C_1{
    using namespace std;
    string linea;
    string fragmento;

    Lexer::Lexer(string file)
    {   
        //transiciones = new int*[36];//[26];
        //for(int i=0 ; i<36 ; i++)
        //    transiciones[i] = new int[26];

        
          ifstream archivo(file);
          
          int filas=0, columnas=0, numero=0;

          if(archivo.fail()){
            cout<<"Error al abrir el archivo";
            exit(1);
          }
          while(!archivo.eof()){
            getline(archivo, linea);
            stringstream input_stringstream(linea); 
            while (getline(input_stringstream, fragmento, ',')){
              if(columnas==26) {
                columnas=0;
                filas+=1;
                transiciones[filas][columnas]=stoi(fragmento);
                //cout << transiciones[filas][columnas] <<"[" <<filas<<","<<columnas<<"]" << endl;
              }else{
                transiciones[filas][columnas]=stoi(fragmento);
                //cout << transiciones[filas][columnas] <<"[" <<filas<<","<<columnas<<"]" << endl;
              }
              columnas=columnas+1;
              

            }  
          }
          archivo.close();



        //PENDIENTE COMPLETAR Y SON 90000

        acc = new bool[36];
        acc[0] = false; 
        acc[1] = true; 
        acc[2] = true;  
        acc[3] = true;  
        acc[4] = true; 
        acc[5] = true; 
        acc[6] = true;  
        acc[7] = true;  
        acc[8] = true; 
        acc[9] = true; 
        acc[10] = true;  
        acc[11] = false;  
        acc[12] = true; 
        acc[13] = true; 
        acc[14] = true;  
        acc[15] = true;  
        acc[16] = true; 
        acc[17] = true; 
        acc[18] = true;  
        acc[19] = true;  
        acc[20] = false; 
        acc[21] = false; 
        acc[22] = true;  
        acc[23] = true;  
        acc[24] = true; 
        acc[25] = true;  
        acc[26] = true;  
        acc[27] = true; 
        acc[28] = true; 
        acc[29] = true;  
        acc[30] = true;  
        acc[31] = true; 
        acc[32] = true;  
        acc[33] = true;  
        acc[34] = true; 
        acc[35] = true; 
        
        
        //PENDIENTE COMPLETAR

        
    }    
        
    Lexer::~Lexer(){
        /*for(int i=0; i<36; i++){
            delete transiciones[i];
        }*/
        //delete transiciones;
        delete acc;
    }

   
    void Lexer::getChar(){ //para que regrese el siguiente caracter del archivo.
         yyin.get(c);
    }
    bool Lexer::openFile(string file){
            yyin.open(file,ios::in);
            if (!yyin.is_open()){
                cerr << "Could not open the file -" << file << "'" <<endl;
                return EXIT_FAILURE;
            }
            getChar();
            return true;
    }
    int Lexer::charToColumn(char c){
        switch (c)
        {
        case '+': return 0; break;
        case '-': return 1; break;
        case '*': return 2; break;
        case '/': return 3; break;
        case ' ': case '\t': case '\n': case '\r': return 4; break;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': return 5; break;
        case 'i': return 6;
        case 'f': return 7;
        case 'e': return 8;
        case 'E': return 9;
        case 'w': return 10;
        case 'l': return 11;
        case 's': return 12;
        case 'h': return 13;
        case 'n': return 14;
        case 't': return 15;
        case 'o': return 16;
        case 'a': return 17;
        
        case 'b':  case 'c':  case 'd':  case 'g':  case 'j':  case 'k': case 'm':  case 'p':  case 'q': 
        case 'r':  case 'u':  case 'v':  case 'x':  case 'y':  case 'z': case 'A':  case 'B':  case 'C':
        case 'D':  case 'F':  case 'G':  case 'H':  case 'I':  case 'J': case 'K':  case 'L':  case 'M':
        case 'N':  case 'O':  case 'P':  case 'Q':  case 'R':  case 'S': case 'T':  case 'U':  case 'V':
        case 'W':  case 'X':  case 'Y':  case 'Z': return 18;

        case '_' : return 19;
        case '.' : return 20;
        case ',' : return 21;
        case ';' : return 22;
        case '(' : return 23;
        case ')' : return 24;
        case '=' : return 25;
        //programación avanzada
        
        default:
            return EXIT_FAILURE;
            break;
        }
    }
    int Lexer::yylex(){
        int q=0;
        int cc=0;
        yytext = "";
        //c='+';
        if(yyin.eof()) return 0;
        while(true){ //true
            if(yyin.eof()) return 0;
            cc= charToColumn(c);
            
            if(transiciones[q][cc] != -1){ //si existe una transicion
                q = transiciones[q][cc]; //vamos al sig estado
                yytext+=c; //se concatena bien rik0
                getChar();//Lee el sig caracter
                if(yyin.eof()) return token(q);
            } else { //no existe una transicion
                if(acc[q]){ //ACEPTACION
                    if(q!=17){
                        return token(q);
                    }
                    else{
                        q=0;
                        yytext="";
                    }
                }else{// ERROR
                    return ERROR;
                }
            }
        }
        
        
    } // Regresa tokens

    int Lexer::token(int q){
        switch(q){
            case 1:
                return MAS;
            case 2:
                return MENOS;
            case 3:
                return MUL;
            case 4:
                return DIV;
            case 5:
                return ASIG;
            case 6:
                return LPAR;
            case 7:
                return RPAR;
            case 8:
                return PYC;
            case 9:
                return COMA;
            case 10:
                return ENTEROS;
            case 19: case 22:
                return FLOTANTES;
            case 24:
                return INT;
            case 28:
                return FLOAT;
            case 31:
                return ELSE;
            case 18:
                return IF;
            case 35:
                return WHILE;     
            case 16: case 12: case 13: case 14: case 15: case 23: case 25: 
            case 26: case 27: case 29:case 30:case 32:case 33: case 34: 
                return ID;
            default:
                return EXIT_FAILURE;
        }//switch
    
    }

    void Lexer::closeFile(){
        yyin.close();
    }
    string Lexer::getYytext(){
        return yytext;
    }
}



/*
#include "Lexer.h"
#include "tokens.h"

namespace COMP{
    Lexer::Lexer()
    {
        transiciones =  new int*[36];
        for(int i=0; i<36; i++) 
            transiciones[i] = new int[25];
        
        // TODO(1)  Completar la tabla de transiciones o llamar a la función para leer el archivo del AFD
        transiciones[0][0] = 1;
        transiciones[0][1] = 2;
        transiciones[0][2] = 3;
        transiciones[0][3] = 4;
        transiciones[0][4] = 5;
        transiciones[0][5] = 17;
        transiciones[0][6] = 10;
        transiciones[0][7] = 16;
        transiciones[0][8] = 16;
        transiciones[0][9] = 14;
        transiciones[0][10] = 13;
        transiciones[0][11] = 16;
        transiciones[0][12] = 12;

        // TODO(2) Completar el arreglo de estados de aceptación
        acc = new bool[36];
        acc[0] = false;
        acc[1] = true;

    }
    
    Lexer::~Lexer()
    {
    }

    bool Lexer::readAFD(string file){
        // TODO(3) Implementar una función qu e lea los renglones de la matriz de transicones
        // y los guarde en dicha matriz
    }

    char Lexer::getChar(){
        // TODO(4) implentar la función que permita regresar solo 1 caracter
    }

    bool Lexer::openFile(string file){
        yyin.open(file,ios::in);
    }

    int Lexer::charToColumn(char c){
        // TODO(5) completar  la función para regresar un número de acuerdo a la columna
        // También se puede usar un map<string, int> para obtenerlo con unbjeto 
        switch ((c))
        {
            case '+': return 0;
            case '-': return 1;
            case '*': return 2;
            case '/': return 3;
            case '=': return 4;
            case ' ': case '\t': case '\r': return 5;
            case '\n':  yyline++; return 5;
        
            default:
                break;
        }
    }

    int Lexer::yylex(){
        int q=0;
        int cc;
        yytext = "";        

        while(true){
            cc = charToColumn(c);
            if(transiciones[q][cc]!=-1){
                q=transiciones[q][cc];
                yytext+=c;
                c= getChar();
            }else{
                if(acc[q]){
                    // TODO(6) Agregar el código para que la función ignore los espacios en blanco.
                    // Hint. Se puede hacer uso del estado de aceptación de los espacios en blanco
                    return token(q);
                }else{
                    return ERROR;
                }
            }
        }

    }

    int Lexer::token(int q){
        // TODO(7) Completar la función para que pueda retornar los tokens
        switch(q){
            case 1:
                return MAS;
            case 2:
                return MENOS;
            case 16:
                return ID;
            
        }
    }

}
*/