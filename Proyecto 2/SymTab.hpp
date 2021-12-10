#ifndef __SYMTAB_HPP__
#define __SYMTAB_HPP__

#include <string>
#include <vector>
#include <map>
using namespace std;

struct Sym{
    int tipo;
    int dir;
    
    std::string categoria; // param, var, func, struct
    std::vector<int> args= vector<int>();
};

class SymTab{
private:
    //    id , Simbolo
    map<string, Sym> syms;
public:
    SymTab();
    ~SymTab();
    // todos los datos del simbolo
    void addSym(string id, int tipo, int dir, string categoria, vector<int> args);
    // Obtiene la dirección
    int getDir(string id);

    // Obtiene el tipo
    int getType(string id);

    // obtiene la categoria
    string getCat(string id);

    // obtiene los args
    vector<int> getArgs(string id);

    // verifica si existe
    bool find(string id);


    map<string,Sym> getSyms();
};

#endif // !__SYMTAB_HPP__