#ifndef __TYPETAB_HPP__
#define __TYPETAB_HPP__

#include <map>
#include <string>
using namespace std;

#include "Type.hpp"

class TypeTab 
{
private:
    map<int,Type> types;
public:
    TypeTab(/* args */);
    ~TypeTab();
    void addType(int id, string name, int tam);
    void addType(int id, string name, int items,  int base);
    void addType(int id, string name, SymTab *tab);
    void addType(int id, string name, int tam ,SymTab *tab);
    int getTam(int id);
    int getItems(int id);
    SymTab *getTab(int id);
    int getBase(int id);
    string getNombre(int id);
};

#endif // !__TYPETAB_HPP__