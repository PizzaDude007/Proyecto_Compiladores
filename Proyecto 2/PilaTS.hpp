#ifndef __PILATS_HPP__
#define __PILATS_HPP__
#include <list>
#include "SymTab.hpp"
using namespace std;


class PilaTS{
private:
    list<SymTab*> data;
public:
    PilaTS();
    ~PilaTS();
    void push(SymTab * ts);
    void pop();
    SymTab* top();
    SymTab* global();
    
};

#endif // !__PILA_HPP__