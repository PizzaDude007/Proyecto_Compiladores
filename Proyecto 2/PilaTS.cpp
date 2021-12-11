#include "PilaTS.hpp"


PilaTS::PilaTS(){

}

PilaTS::~PilaTS(){

}

void PilaTS::push(SymTab * ts){
    data.push_back(ts);
}

void PilaTS::pop(){
    data.pop_back();
}

SymTab* PilaTS::top(){
    return data.back();
}

SymTab* PilaTS::global(){
    return data.front();
}