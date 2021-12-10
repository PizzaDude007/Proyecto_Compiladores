#ifndef __TYPETAB_HPP__
#define __TYPETAB_HPP__

#include <map>
#include <string>
#include <vector>
#include "SymTab.hpp"

using namespace std;



struct Type {
    string name;
    int tam;
    SymTab *tipoBase = NULL;
    //int items; // Tal vez para arreglos
    
};

class TypeTab {
private:
    map<int,Type> types;
public:
    // constructor
    TypeTab(/* args */);
    ~TypeTab();
    //agregar tipos nativos
    void addType(int id, string name, int tam);
    //agregar structs
    void addType(int id, string name, int tam ,SymTab *tab);
    string getNombre(int id);
    int getTam(int id);
    SymTab *getTipoBase(int id);
    
};

#endif // !__TYPETAB_HPP__