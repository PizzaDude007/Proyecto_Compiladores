#include "Driver.hpp"
#include <iostream>
#include <sstream>



Driver::Driver(){
    // se agrega la tabla de simbolos global
    SymTab *TSglobal= new SymTab(); // tabla global
    pilaTS.push(TSglobal);

    // instancia de pilas
    pilaEtq=stack<string>();
    pilaTemp= stack<int>();
    pilaDir= stack<int>();


    //valores iniciales
    tipoRetorno=0;
    tieneRetorno=false;
    dir=0;
    numEtiquetas=0;
    numTemporales=0;
    cteFloat=0;
    cteDouble=0;
    numLabel=0;
    contType=0;
    
}

int Driver::agregar_tipo(std::string nombre, int tam_bytes, SymTab *tipo_base){
    Ttipos.addType(contType++, nombre,tam_bytes , tipo_base);
}

void Driver::crear_ambito(){
    SymTab *ts = new SymTab();
    pilaTS.push(ts); //insertar en pila
    pilaDir.push(dir);
    dir = 0;
    pilaTemp.push(numTemporales);
    numTemporales = 0;    
}

void Driver::destruir_ambito(){
    //recuperar valores de las pilas temporales y la dir global
    
    // se elimina la TS 
    pilaTS.pop();
    
    // se recupera el dir
    dir= pilaDir.top();
    pilaDir.pop();

    // se recupera el num de temporales
    numTemporales=pilaTemp.top();
    pilaTemp.pop();

}


void Driver::agregar_simbolo(std::string id, int tipo, std::string categoria){ 
    
    SymTab *tablaSimbolo = pilaTS.top();

    if (!tablaSimbolo->find(id)){
        tablaSimbolo->addSym(id,tipo,dir++,categoria,vector<int>());
    }else{
        error_semantico("El id ["+id+"] que esta intentando agregar ya existe.");
    }

    
    
}
 
void Driver::agregar_simbolo(std::string id, int tipo, std::vector<int> args){//Funciones
    SymTab *tablaSimbolo = pilaTS.top();
    if (!tablaSimbolo->find(id)){
        tablaSimbolo->addSym(id,tipo,dir++,"func",args);
    }else{
        error_semantico("El id ["+id+"] que esta intentando agregar ya existe.");
    }
}

string Driver::nuevaEtiqueta(){
    stringstream label;
    label<< "L"<<numLabel++;
    return label.str();
}

string Driver::nuevaTemporal(){
    stringstream temp;
    temp<<"t"<<numTemporales++;
    return temp.str();
}

Expresion Driver::asignacion(std::string id, Expresion e){
    Expresion e1;
    string alfa;
    //Validar que el id fue declarado
    if(!pilaTS.top()->find(id)) error_semantico("La variable "+id+" no fue declarada");
    int typeId = pilaTS.top()->getType(id);
    e1.tipo = typeId; //La expresión de salida siempre tendrá el tipo del id
    if(typeId == e.tipo){
        alfa = e.dir;
    }
    else if(typeId>e.tipo)
    {
        alfa = ampliar(e.dir, e.tipo, e1.tipo);
    }
    else if(minimo(typeId, e.tipo)!=1)
    {    
        alfa = reducir(e.dir, e.tipo, e1.tipo);        
    }
    else
    {
        error_semantico("Los tipos son incompatibles");
    }
    //genCode(id, alfa, "=", "");
    e.dir = id;        
    return e1;
}


bool Driver::compatibles(int t1, int t2){
    std::string nombre = Ttipos.getNombre(t1);
    std::string nombre2 = Ttipos.getNombre(t2);
    if(nombre == "struct" && nombre2=="struct"){
        map<string,Sym> ts1 = Ttipos.getTipoBase(t1)->getSyms();
        map<string,Sym> ts2 = Ttipos.getTipoBase(t2)->getSyms();

        map<string,Sym>::iterator it;

        // contamos los tipos de ts1
        int tipos1[6]={0,0,0,0,0,0};
        for(it=ts1.begin(); it!= ts1.end();it++){
            //incrementa el tipo al que pertenece
            tipos1[it->second.tipo]++; 
        }
        
        // contamos tipos de ts1
        int tipos2[6]={0,0,0,0,0,0};
        for(it=ts2.begin(); it!= ts2.end();it++){
            //incrementa el tipo al que pertenece
            tipos2[it->second.tipo]++; 
        }

        // comparamos tipos
        for (size_t i = 0; i < 6; i++)
        {
            if (tipos1[i] != tipos2[i]){ // si uno es diferente no es compatible
                return false;
            }
        }
        return true;
    }
    if(t1==t2) return true;
    if(t1 == 1 || t2 == 2) return true;
    return false;
}

Expresion Driver::numero(std::string val, int tipo){ //Para constantes o double
    Expresion e; //como devuelve? 
    //[usar Expresion en lugar de Numero]
    Numero num;
    if(tipo == 3){ // flotante
        //doble o flotante
        stringstream cte;
        cte<<"cteFloat"<<cteFloat++;
        num.val = val;
        num.tipo = tipo;
        constantes[cte.str()] = num;
    }else if(tipo==4) //double
    {
        stringstream cte;
        cte<<"cteDouble"<<cteDouble++;
        num.val = val;
        num.tipo = e.tipo = tipo;
        constantes[cte.str()] = num;
    }else{ //entero
        num.val=val; //Falta contador?
        num.tipo=tipo;
    }
    
}


Expresion Driver::suma(Expresion o1, Expresion o2){
    Expresion exp;
    exp.tipo = maximo(o1.tipo, o2.tipo);

    if (exp.tipo != -1){
        exp.dir = nuevaTemporal();
        string str1 = ampliar(o1.dir,o1.tipo,exp.tipo);
        string str2 = ampliar(o2.dir, o2.tipo, exp.tipo);
        codigo_intermedio.push_back(nuevaCuadrupla(str1,str2,"+",exp.dir));
        
    }else{
        error_semantico("Tipos Incompatibles");
    }
    return exp;

}

Expresion Driver::mul(Expresion e1, Expresion e2){
    Expresion e;
    
    e.tipo = max(e1.tipo, e2.tipo);
    if(e.tipo!=-1){
        e.dir=nuevaTemporal();
        string alfa1 = ampliar(e1.dir, e1.tipo, e.tipo);
        string alfa2 = ampliar(e2.dir, e2.tipo, e.tipo);
        codigo_intermedio.push_back(nuevaCuadrupla(alfa1,alfa2,"*",e.dir));
    }else{
        error_semantico("Los tipos son incompatibles");
    }
    return e;
}

Expresion Driver::resta(Expresion o1, Expresion o2){
    Expresion exp;
    exp.tipo = maximo(o1.tipo, o2.tipo);

    if (exp.tipo != -1){
        exp.dir = nuevaTemporal();
        string str1 = ampliar(o1.dir,o1.tipo,exp.tipo);
        string str2 = ampliar(o2.dir, o2.tipo, exp.tipo);
        codigo_intermedio.push_back(nuevaCuadrupla(str1,str2,"-",exp.dir));

    }else{
        error_semantico("Tipos Incompatibles");
    }
    return exp;

}

Expresion Driver::division(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = max(e1.tipo, e2.tipo);
    if(e.tipo!=-1){
        e.dir=nuevaTemporal();
        string alfa1 = ampliar(e1.dir, e1.tipo, e.tipo);
        string alfa2 = ampliar(e2.dir, e2.tipo, e.tipo);
        codigo_intermedio.push_back(nuevaCuadrupla(alfa1,alfa2,"/",e.dir));

    }else{
        error_semantico("Los tipos son incompatibles");
    }
    return e;
}

Expresion Driver::disyuncion(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = 2;   //Depende de la tabla de tipos donde pongamos int.
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = "||";
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }
}
Expresion Driver::igual(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = 2;   //Depende de la tabla de tipos donde pongamos int.
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = "==";
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }    
}
Expresion Driver::mayor_que(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = 2;   //Depende de la tabla de tipos donde pongamos int.
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = ">";
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }    
}
Expresion Driver::mayor_o_igual(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = 2;   //Depende de la tabla de tipos donde pongamos int.
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = "<";
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }
}
Expresion Driver::menor_o_igual(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = 2;   //Depende de la tabla de tipos donde pongamos int.
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = "<=";
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }    
}
Expresion Driver::distinto(Expresion e1, Expresion e2){
    Expresion e;
    e.tipo = 2;   //Depende de la tabla de tipos donde pongamos int.
    e.dir = nuevaTemporal();
    if(compatibles(e1.tipo, e2.tipo)){
        Cuadrupla c;
        c.arg1 = e1.dir;
        c.arg2 = e2.dir;
        c.resultado = e.dir;
        c.operador = "!=";
        codigo_intermedio.push_back(c);
    }else{
        error_semantico("Los tipos de los operandos son incompatibles");
    }    
}
Expresion Driver::negacion(Expresion e1){
    Expresion e;
    e.tipo = 2;   //Depende de la tabla de tipos donde pongamos int.
    e.dir = nuevaTemporal();
   
    Cuadrupla c;
    c.arg1 = e1.dir;
    c.arg2 = "";
    c.resultado = e.dir;
    c.operador = "!";
    codigo_intermedio.push_back(c);

}
Expresion Driver::identificador(std::string id){
    Expresion e;
    if(pilaTS.top()->find(id)){ //Se válida que exista el id
        e.dir = id;
        e.tipo = pilaTS.top()->getType(id);  // Se obtiene el tipo del id
    }else{
        error_semantico("El identificador "+ id + " no fue declarado");
    }
    return e;   
}

string Driver::ampliar(std::string dir, int t1, int t2){
    string temp;
    if(t1==t2) return dir;
    else if(t1==2 && t2==3 || t1==3 && t2==2){
        temp = nuevaTemporal();
        //icode.push_back(Cuadrupla("(float)",dir, "", temp));
        agregar_simbolo("temporal", 3, temp);
        return temp;
    }else if(t1==3 && t2==4 || t1==4 && t2==3){
        temp = nuevaTemporal();
        //icode.push_back(Cuadrupla("(float)",dir, "", temp));
        agregar_simbolo("temporal", 4, temp); //El id es del mas grande?
        return temp;
    }else if(t1==2 && t2==4 || t1==4 && t2==2){
        temp = nuevaTemporal();
        //icode.push_back(Cuadrupla("(float)",dir, "", temp));
        agregar_simbolo("temporal", 4, temp); //El id es del mas grande?
        return temp;
    }else return "";
}

string Driver::reducir(std::string dir, int t1, int t2){
    string temp;
    if(t1==t2) return dir;
    else if(t1==2 && t2==3 || t1==3 && t2==2){
        temp = nuevaTemporal();
        //icode.push_back(Cuadrupla("(float)",dir, "", temp));
        agregar_simbolo("temporal", 2, temp);
        return temp;
    }else if(t1==3 && t2==4 || t1==4 && t2==3){
        temp = nuevaTemporal();
        //icode.push_back(Cuadrupla("(float)",dir, "", temp));
        agregar_simbolo("temporal", 3, temp); //El id es del mas grande?
        return temp;
    }else if(t1==2 && t2==4 || t1==4 && t2==2){
        temp = nuevaTemporal();
        //icode.push_back(Cuadrupla("(float)",dir, "", temp));
        agregar_simbolo("temporal", 2, temp); //El id es del mas grande?
        return temp;
    }else return "";
}

int Driver::maximo(int t1, int t2){
    if(t1==t2) return t1;
    else if(t1==2 && t2==3) return 3;
    else if(t1==2 && t2==4) return 4;
    else if(t1==3 && t2==2) return 3;
    else if(t1==3 && t2==4) return 4;
    else if(t1==4 && t2==2) return 4;
    else if(t1==4 && t2==3) return 4;
    else return -1;
}

int Driver::minimo(int t1, int t2){
    if(t1==t2) return t1;
    else if(t1==2 && t2==3) return 2;
    else if(t1==2 && t2==4) return 2;
    else if(t1==3 && t2==2) return 2;
    else if(t1==3 && t2==4) return 3;
    else if(t1==4 && t2==2) return 2;
    else if(t1==4 && t2==3) return 3;
    else return -1;
}

void Driver::error_semantico(std::string mensaje){
    cout<<"Error semántico "<<mensaje<<endl;
    exit(EXIT_FAILURE);
}

void Driver::gen_imprimir(string val){
    
    // for(vector<Cuadrupla>::iterator q = codigo_intermedio.begin(); q != codigo_intermedio.end(); q++)
    // {
    //     //string operador = *q.operador;
    //     int compare = str2int((*q).operador.c_str());
    //     switch(compare){
    //     case str2int("+"): 
    //     case str2int("-"):
    //     case str2int("*"):
    //     case str2int("/"):
    //         cout<<q->resultado<<"="<<q->arg1<<q->operador<<q->arg2<<endl;
    //         break;
    //     case str2int("if"):
    //         cout<<q->operador<<" "<<q->arg1<<" goto "<<q->resultado<<endl;
    //         break;
    //     case str2int("goto"):
    //         cout<<q->operador<<" "<<q->resultado<<endl;
    //         break;
    //     case str2int("="):
    //         cout<<q->resultado<<q->operador<<q->arg1<<endl;
    //         break;
    //     case str2int("label"):
    //         cout<<q->resultado<<":";
    //         break;
    //     case str2int("(float)"):
    //     case str2int("(int)"):
    //         cout<<q->resultado<<"="<<q->operador<<q->arg1<<endl;
    //     case str2int("scan"):
    //         cout<<"scan "<<q->resultado<<endl;
    //         break;
    //     } 

    // }
    // cout<<endl;    

}

void Driver::gen_lectura(string dir){
    //Leyendo 7u7
    Cuadrupla c1 = nuevaCuadrupla("", "scan", "", dir); 
    codigo_intermedio.push_back(c1);
/*  c1.arg1 ;
    c1.operador = "scan"; // a partir de este se genera el codigo intermedio.
    c1.arg2 = ""; 
    c1.resultado = dir; */
    // li $v0, 5
    // la $t0, dir
    // syscall
}

string Driver::gen_label(string label){
    stringstream label_l;
    label_l<< label <<numLabel++; //Label se cambio por L...
    return label_l.str();    
}

void Driver::gen_goto(string label){
    Cuadrupla c1; 
    c1.arg1 = "goto";
    c1.operador = "";
    c1.arg2 = ""; 
    c1.resultado = label;
    codigo_intermedio.push_back(c1);
}

void Driver::gen_if(string var, string ltrue, string lfalse){
    Cuadrupla c1, c2;
    c1.arg1 = "if";
    c1.operador = var;
    c1.arg2 = "goto"; 
    c1.resultado = ltrue;
    codigo_intermedio.push_back(c1);

    c2.arg1 = "goto";
    c2.operador = "";
    c2.arg2 = ""; 
    c2.resultado = lfalse;
    codigo_intermedio.push_back(c2);  
}

struct Cuadrupla Driver::nuevaCuadrupla(string arg1, string arg2, string operador, string resultado){
    Cuadrupla temp;
    temp.arg1 = arg1;
    temp.arg2 = arg2;
    temp.operador = operador;
    temp.resultado = resultado;
    return temp;
}

int Driver::calcularTamanio(SymTab){

}



