#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__
#include <string>
#include <map>
#include <stack>
#include <vector>
#include <list> 
#include "TypeTab.hpp"
#include "PilaTS.hpp"
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



//
class Driver{
private:
    // tabla de tipos
    TypeTab Ttipos;
    // Tabla de cadenas
    std::map<std::string, std::string> Tstring; 
    // Tabla de flotantes constantes
    std::map <std::string, Numero> constantes;

    //Pila de tabla de simbolos
    PilaTS pilaTS;
        
    std::stack<std::string> pilaEtq; //Pila para etiquetas next
    std::stack<int> pilaDir; // Pila para dir cuando cambia de contexto
    std::stack<int> pilaTemp; // Pila para guardar temporales


    
    int tipoRetorno;
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
    
    //[To do]Debes agregar estructuras y nativo
    int agregar_tipo(std::string nombre, int tam_bytes, SymTab *tipo_base); //ya esta

    //agrega variables
    void agregar_simbolo(std::string id, int tipo, std::string categoria);  // ya

    //agrega funciones
    void agregar_simbolo(std::string id, int tipo, std::vector<int> args); // ya funcion
    
    string nuevaEtiqueta(); // ya
    string nuevaTemporal(); // ya


    Expresion asignacion(std::string id, Expresion e); 
    Expresion suma(Expresion e1, Expresion e2); //Ya +-
    Expresion mul(Expresion e1, Expresion e2); //Ya +-
    Expresion resta(Expresion e1, Expresion e2); //Ya +-
    Expresion division(Expresion e1, Expresion e2); //Ya +-
    Expresion disyuncion(Expresion e1, Expresion e2); //Ya
    Expresion conjuncion(Expresion e1, Expresion e2); 
    Expresion igual(Expresion e1, Expresion e2); //Ya
    Expresion menor_que(Expresion e1, Expresion e2); 
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

    // compatibles con mismo numero y tipo de campos
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