#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <list> 
#include "TypeTab.hpp"
using namespace std;
 
struct Cuadrupla{
    std::string arg1;
    std::string arg2;
    std::string operador;
    std::string resultado;
};
//class SymTab; 
struct Expresion{
    std::string dir;
    int tipo; 
}; 

struct Numero{
    std::string val;
    int tipo;
};

struct SymTab{
    std::string dir;
    int tipo;
    std::string cat;
    std::vector<int> args=vector<int>();
};
//
class PilaTS{
    private:
        vector<SymTab*> datos;
};
//
class Driver{
private:
    TypeTab tt;
    //Pila de tabla de simbolos

    list<map<string,SymTab>> pilaTS;
        // .push_back( e )   -> para agregar al final de la cola
        // .pop_back()       -> para eliminar al final de la cola
        // .front()          -> para acceder al primer elemento (global)
        // .back()           -> para accedeer al tope(final) de la pila
    std::stack<std::string> pilaEtiquetas; //Pila para etiquetas
    std::stack<int> pilaDir;
    std::stack<int> pilaTemporal;
    std::map<std::string, std::string> tstring;
    std::map <std::string, Numero> constantes;
    
    int retorno;
    bool tieneRetorno;
    int dir;
    int numEtiquetas;
    int numTemporales;
    int cteFloat;
    int cteDouble;
    int numLabel;
    int contType;
    std::vector<Cuadrupla> codigo_intermedio;
    //Generador de codigo final
public:
    Driver();
    ~Driver();
    //Funciones para tabla de tipos
    int agregar_tipo(std::string nombre, int tam_bytes, SymTab *tipo_base); //ya esta
    void agregar_simbolo(std::string id, int tipo, std::string categoria);  // ya
    void agregar_simbolo(std::string id, int tipo, std::vector<int> args); // ya funcion
    string nuevaEtiqueta(); // ya
    string nuevaTemporal(); // ya


    void funcion();
    Expresion asignacion(std::string id, Expresion e); 
    Expresion suma(Expresion e1, Expresion e2); //Ya +-
    Expresion mul(Expresion e1, Expresion e2); //Ya +-
    Expresion resta(Expresion e1, Expresion e2); //Ya +-
    Expresion division(Expresion e1, Expresion e2); //Ya +-
    Expresion disyuncion(Expresion e1, Expresion e2); //Ya
    Expresion igual(Expresion e1, Expresion e2); //Ya
    Expresion mayor_que(Expresion e1, Expresion e2); //Ya
    Expresion mayor_o_igual(Expresion e1, Expresion e2); //Ya
    Expresion menor_o_igual(Expresion e1, Expresion e2); //Ya
    Expresion distinto(Expresion e1, Expresion e2); //Ya
    Expresion negacion(Expresion e1);
    Expresion identificador(std::string id);
    Expresion numero(std::string val, int tipo);
    //To do: [agregar una para validar asignacion de estructuras]
    std::string ampliar(std::string dir, int t1, int t2); //Ya
    std::string reducir(std::string dir, int t1, int t2); //Ya
    int maximo(int t1, int t2);
    int minimo(int t1, int t2);
    bool compatibles(int t1, int t2);

    void error_semantico(std::string mensaje);
    void gen_imprimir(string val);
    void gen_lectura(string dir);
    string gen_label(string label);
    void gen_goto(string label);
    void gen_if(string var, string ltrue, string lfalse);

    void Driver::crear_ambito();
    void Driver::destruir_ambito();

    struct Cuadrupla nuevaCuadrupla(string arg1, string arg2, string operador, string resultado);
    //constexpr unsigned int str2int(const char* str, int h = 0);

};


#endif // !__DRIVER_HPP__