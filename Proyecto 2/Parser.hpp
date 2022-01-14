#include <string>
#include <map>
#include <stack>
#include <vector>
#include "Driver.hpp"


enum NoTerminales{
    programa,
    declaraciones,
    declaraciones_,
    declaracion,
    lista_var,
    lista_var_
};

enum Token{
    FINARCHIVO = 0,
    PYC,
    COMA,
    ID
};

// para saber si es terminal o no terminal
enum TipoSimbolo{
    ts_noterminal,
    ts_terminal,
    ts_accion
};

struct Produccion
{
    //encabezado
    int head;
    vector<int> body;
    Produccion(int head, vector<int> body){
        this->head = head;
        this->body =body;
    };

    Produccion() = default;

};

struct SimboloP{
    TipoSimbolo tipo;
    string name;
    int id;
    SimboloP(string name, TipoSimbolo tipo, int id){
        this->name=name;
        this->tipo=tipo;
        this->id = id;
    };
    SimboloP()=default;
};

class Parser {
private:
    Lexer *lexer;
    Token token;
    map<Token string> TOK;
    Driver semantic;
    map<int,SimboloP> simbolos;
    map<int,Produccion> producciones;
public:
    Parser();
    Parser(Lexer * lexer);
    ~Parser();
    
    void programa();
    void prod

}