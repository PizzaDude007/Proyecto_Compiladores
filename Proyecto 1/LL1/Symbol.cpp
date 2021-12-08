#include "Symbol.h"

Symbol::Symbol(/* args */)
{
    
}

Symbol::~Symbol()
{

}

void Symbol::setName(string name){
    name = name;
}
void Symbol::setType(TYPESYM ty){
    type = ty;
}
void Symbol::setId(int id){
    id = id;
}  
int Symbol::getId(){
    return id;
}
string Symbol::getName(){
    return name;
}
TYPESYM Symbol::getType(){
    return type;
}