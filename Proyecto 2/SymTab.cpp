#include "SymTab.hpp"

SymTab::SymTab()
{
}

SymTab::~SymTab()
{
}

/*
 * Agrega un símbolo a la tabla de símbolos
 */
void SymTab::addSym(string id, int tipo, int dir, string categoria, vector<int> args)
{
    Sym s;
    s.tipo= tipo;
    s.dir=dir;
    s.categoria=categoria;
    s.args=args;

    syms[id] = s;
}

/*******************************************************************************/
/*    Funciones para acceder a la información en la tabla de símbolos **********/
/*******************************************************************************/

int SymTab::getDir(string id)
{
    return syms[id].dir;
}

int SymTab::getType(string id)
{
    return syms[id].tipo;
}

string SymTab::getCat(string id)
{
    return syms[id].categoria;
}

vector<int> SymTab::getArgs(string id)
{
    return syms[id].args;
}

bool SymTab::find(string id)
{
    map<string,Sym>::iterator it;
    it = syms.find(id);
    return it != syms.end(); 
}

map<string,Sym> SymTab::getSyms()
{
    return syms;
}