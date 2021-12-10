#include "TypeTab.hpp"

TypeTab::TypeTab(/* args */)
{
}

TypeTab::~TypeTab()
{
}

/*
 * Función para agregar un tipo nativo en la tabla de tipos
 */
void TypeTab::addType(int id, string name, int tam)
{
    Type tipo ;
    tipo.name = name;
    tipo.tam = tam;
    tipo.tipoBase= NULL;

    types[id] =tipo;
}

/*
 * Función para agregar un tipo struct en la tabla de tipos
 */
void TypeTab::addType(int id, string name, int tam , SymTab *tab)
{
    Type tipo ;
    tipo.name = name;
    tipo.tam = tam;
    tipo.tipoBase= tab;
    types[id] = tipo;
}

/*
 * Función para agregar un tipo de array en la tabla de tipos
 */
// void TypeTab::addType(int id, string name, int items,  int base)
// {
//     int tam = types[base].getTam()*items;
//     types[id] = Type(name, items, base, tam);
// }


/****************************************************************************************/
/* Funciones para devolver las características de un tipo de acuerdo a su identificador */
/****************************************************************************************/


string TypeTab::getNombre(int id)
{
    return types[id].name;
}

int TypeTab::getTam(int id)
{
    return types[id].tam;
}


SymTab *TypeTab::getTipoBase(int id)
{
    return types[id].tipoBase;
}

