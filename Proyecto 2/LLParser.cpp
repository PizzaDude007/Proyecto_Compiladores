#include <string>
#include <map>
#include <vector>
#include <stack>
#include "Lexer.h"
#include "Driver.hpp"


enum NoTerm {
	declaraciones,
	declaracion,
	declaracion1,
	declaracion2,
	declaracion3,
	tipo,
	lista_var,
	lista_var_,
	body_struct,
	lista_args,
	args,
	args_,
	arg,
	decl_locales,
	decl_local,
	bloque_sentencias,
	sentencias,
	sentencias_,
	sentencia,
	sentencia1,
	sentIf,
	sentWhile,
	sentDo,
	sentAsig,
	sentIf_,
	parte_izq,
	parte_izq_,
	sentScan,
	sentBreak,
	sentReturn,
	sentReturn_,
	expresion,
	expresion_,
	expresion1,
	expresion1_,
	expresion2,
	expresion2_,
	expresion3,
	expresion3_,
	expresion4,
	expresion4_,
	expresion5,
	expresion5_,
	expresion6,
	expresion7,
	expresion7_,
	lista_params,
	params,
	params_,
	param,
	bloque_o_sentencia,
	programa,
};


enum Token {
	ENDF= 0,
	PUNTO_COMA,
	COMA,
	PUNTO,
	ESTRUCTURA,
	VACIO,
	DEVUELVE,
	IDENTIFICADOR,
	PAR_IZQ,
	PAR_DER,
	LLAVE_IZQ,
	LLAVE_DER,
	SI,
	SINO,
	MIENTRAS,
	HACER,
	INTERRUMPE,
	IGUAL,
	MAS,
	MENOS,
	MULTIPLICACION,
	DIVISION,
	ENTERO,
	FLOTANTE,
	CHAR,
	NUM_DOBLE,
	NUMERO,
	FLOTANTES,
	DOBLES,
	CARACTERES,
	CARACTER,
	IMPRIME,
	ESCANER,
	DISYUNCION,
	CONJUNCION,
	IGUALDAD,
	NEGACION,
	DIFERENTE,
	MAYOR,
	MENOR,
	MAYOR_IGUAL,
	MENOR_IGUAL,
};


enum LLSymType {
	ll_terminal,
	ll_noterminal,
	ll_action
};

struct LLSymbol
{
	LLSymType type;
	std::string name;
	std::string object;
	int idx;
	LLSymbol(std::string name, std::string object, LLSymType type, int idx ){
		this->name = name;
		this->object = object;
		this->type = type;
		this->idx = idx;
	}
	LLSymbol()=default;
};

typedef std::vector<int> Body;
struct LLProduction{
	int head;
	std::vector<int> body;
	LLProduction(int head, Body body){
		this->head = head;
		this->body = body;
	}
	LLProduction()=default;
};

struct LLGrammar{
	std::map<int, LLSymbol> ll_symbols = {
		{0,{"PUNTO_COMA", "", ll_terminal, PUNTO_COMA}},
		{1,{"COMA", "", ll_terminal, COMA}},
		{2,{"PUNTO", "", ll_terminal, PUNTO}},
		{3,{"ESTRUCTURA", "", ll_terminal, ESTRUCTURA}},
		{4,{"VACIO", "", ll_terminal, VACIO}},
		{5,{"DEVUELVE", "", ll_terminal, DEVUELVE}},
		{6,{"IDENTIFICADOR", "string", ll_terminal, IDENTIFICADOR}},
		{7,{"PAR_IZQ", "", ll_terminal, PAR_IZQ}},
		{8,{"PAR_DER", "", ll_terminal, PAR_DER}},
		{9,{"LLAVE_IZQ", "", ll_terminal, LLAVE_IZQ}},
		{10,{"LLAVE_DER", "", ll_terminal, LLAVE_DER}},
		{11,{"SI", "", ll_terminal, SI}},
		{12,{"SINO", "", ll_terminal, SINO}},
		{13,{"MIENTRAS", "", ll_terminal, MIENTRAS}},
		{14,{"HACER", "", ll_terminal, HACER}},
		{15,{"INTERRUMPE", "", ll_terminal, INTERRUMPE}},
		{16,{"IGUAL", "", ll_terminal, IGUAL}},
		{17,{"MAS", "", ll_terminal, MAS}},
		{18,{"MENOS", "", ll_terminal, MENOS}},
		{19,{"MULTIPLICACION", "", ll_terminal, MULTIPLICACION}},
		{20,{"DIVISION", "", ll_terminal, DIVISION}},
		{21,{"ENTERO", "", ll_terminal, ENTERO}},
		{22,{"FLOTANTE", "", ll_terminal, FLOTANTE}},
		{23,{"CHAR", "", ll_terminal, CHAR}},
		{24,{"NUM_DOBLE", "", ll_terminal, NUM_DOBLE}},
		{25,{"NUMERO", "int", ll_terminal, NUMERO}},
		{26,{"FLOTANTES", "float", ll_terminal, FLOTANTES}},
		{27,{"DOBLES", "double", ll_terminal, DOBLES}},
		{28,{"CARACTERES", "string", ll_terminal, CARACTERES}},
		{29,{"CARACTER", "char", ll_terminal, CARACTER}},
		{30,{"IMPRIME", "", ll_terminal, IMPRIME}},
		{31,{"ESCANER", "", ll_terminal, ESCANER}},
		{32,{"DISYUNCION", "", ll_terminal, DISYUNCION}},
		{33,{"CONJUNCION", "", ll_terminal, CONJUNCION}},
		{34,{"IGUALDAD", "", ll_terminal, IGUALDAD}},
		{35,{"NEGACION", "", ll_terminal, NEGACION}},
		{36,{"DIFERENTE", "", ll_terminal, DIFERENTE}},
		{37,{"MAYOR", "", ll_terminal, MAYOR}},
		{38,{"MENOR", "", ll_terminal, MENOR}},
		{39,{"MAYOR_IGUAL", "", ll_terminal, MAYOR_IGUAL}},
		{40,{"MENOR_IGUAL", "", ll_terminal, MENOR_IGUAL}},
		{41,{"$", "", ll_terminal, ENDF}},
		{42,{"declaraciones", "", ll_noterminal, declaraciones}},
		{43,{"declaracion", "Expresion", ll_noterminal, declaracion}},
		{44,{"declaracion1", "Expresion", ll_noterminal, declaracion1}},
		{45,{"declaracion2", "Expresion", ll_noterminal, declaracion2}},
		{46,{"declaracion3", "Expresion", ll_noterminal, declaracion3}},
		{47,{"tipo", "int", ll_noterminal, tipo}},
		{48,{"lista_var", "Expresion", ll_noterminal, lista_var}},
		{49,{"lista_var_", "Expresion", ll_noterminal, lista_var_}},
		{50,{"body_struct", "", ll_noterminal, body_struct}},
		{51,{"lista_args", "Expresion", ll_noterminal, lista_args}},
		{52,{"args", "Expresion", ll_noterminal, args}},
		{53,{"args_", "Expresion", ll_noterminal, args_}},
		{54,{"arg", "int", ll_noterminal, arg}},
		{55,{"decl_locales", "", ll_noterminal, decl_locales}},
		{56,{"decl_local", "", ll_noterminal, decl_local}},
		{57,{"bloque_sentencias", "", ll_noterminal, bloque_sentencias}},
		{58,{"sentencias", "", ll_noterminal, sentencias}},
		{59,{"sentencias_", "", ll_noterminal, sentencias_}},
		{60,{"sentencia", "", ll_noterminal, sentencia}},
		{61,{"sentencia1", "", ll_noterminal, sentencia1}},
		{62,{"sentIf", "", ll_noterminal, sentIf}},
		{63,{"sentWhile", "", ll_noterminal, sentWhile}},
		{64,{"sentDo", "", ll_noterminal, sentDo}},
		{65,{"sentAsig", "", ll_noterminal, sentAsig}},
		{66,{"sentIf_", "string", ll_noterminal, sentIf_}},
		{67,{"parte_izq", "Expresion", ll_noterminal, parte_izq}},
		{68,{"parte_izq_", "Expresion", ll_noterminal, parte_izq_}},
		{69,{"sentScan", "", ll_noterminal, sentScan}},
		{70,{"sentBreak", "", ll_noterminal, sentBreak}},
		{71,{"sentReturn", "", ll_noterminal, sentReturn}},
		{72,{"sentReturn_", "Expresion", ll_noterminal, sentReturn_}},
		{73,{"expresion", "Expresion", ll_noterminal, expresion}},
		{74,{"expresion_", "Expresion", ll_noterminal, expresion_}},
		{75,{"expresion1", "Expresion", ll_noterminal, expresion1}},
		{76,{"expresion1_", "Expresion", ll_noterminal, expresion1_}},
		{77,{"expresion2", "Expresion", ll_noterminal, expresion2}},
		{78,{"expresion2_", "Expresion", ll_noterminal, expresion2_}},
		{79,{"expresion3", "Expresion", ll_noterminal, expresion3}},
		{80,{"expresion3_", "Expresion", ll_noterminal, expresion3_}},
		{81,{"expresion4", "Expresion", ll_noterminal, expresion4}},
		{82,{"expresion4_", "Expresion", ll_noterminal, expresion4_}},
		{83,{"expresion5", "Expresion", ll_noterminal, expresion5}},
		{84,{"expresion5_", "Expresion", ll_noterminal, expresion5_}},
		{85,{"expresion6", "Expresion", ll_noterminal, expresion6}},
		{86,{"expresion7", "Expresion", ll_noterminal, expresion7}},
		{87,{"expresion7_", "Expresion", ll_noterminal, expresion7_}},
		{88,{"lista_params", "Expresion", ll_noterminal, lista_params}},
		{89,{"params", "Expresion", ll_noterminal, params}},
		{90,{"params_", "Expresion", ll_noterminal, params_}},
		{91,{"param", "int", ll_noterminal, param}},
		{92,{"bloque_o_sentencia", "", ll_noterminal, bloque_o_sentencia}},
		{93,{"programa", "", ll_noterminal, programa}},
	};

	std::map<int, LLProduction> prods = {
		{1,{49,{ 48, }}},
		{2,{48,{ 45, 48, }}},
		{3,{48,{ }}},
		{4,{45,{ 52, 10, 46, }}},
		{5,{45,{ 5, 50, }}},
		{6,{45,{ 11, 10, 2, 58, 14, 15, 62, 61, 12, }}},
		{7,{46,{ 53, 6, }}},
		{8,{46,{ 2, 58, 14, 15, 62, 61, 12, }}},
		{9,{50,{ 10, 40, }}},
		{10,{50,{ 55, 35, 6, }}},
		{11,{40,{ 55, 35, 6, }}},
		{12,{40,{ 10, 2, 58, 14, 15, 62, 61, 12, }}},
		{13,{52,{ 18, }}},
		{14,{52,{ 25, }}},
		{15,{52,{ 26, }}},
		{16,{52,{ 30, }}},
		{17,{55,{ 15, 62, 12, }}},
		{18,{35,{ 10, 53, }}},
		{19,{53,{ 7, 10, 53, }}},
		{20,{53,{ }}},
		{21,{58,{ 56, }}},
		{22,{58,{ }}},
		{23,{56,{ 60, 59, }}},
		{24,{59,{ 7, 60, 59, }}},
		{25,{59,{ }}},
		{26,{60,{ 52, 10, }}},
		{27,{62,{ 54, 62, }}},
		{28,{62,{ }}},
		{29,{54,{ 52, 35, 6, }}},
		{30,{61,{ 63, }}},
		{31,{61,{ }}},
		{32,{63,{ 64, 57, }}},
		{33,{57,{ 64, 57, }}},
		{34,{57,{ }}},
		{35,{64,{ 66, }}},
		{36,{64,{ 67, }}},
		{37,{64,{ 69, }}},
		{38,{64,{ 76, }}},
		{39,{64,{ 51, }}},
		{40,{64,{ 78, }}},
		{41,{64,{ 75, }}},
		{42,{64,{ 33, 2, 68, }}},
		{43,{68,{ 16, 14, 6, }}},
		{44,{68,{ 82, 14, 6, }}},
		{45,{66,{ 13, 2, 82, 14, 73, 71, }}},
		{46,{71,{ 17, 73, }}},
		{47,{71,{ }}},
		{48,{67,{ 8, 2, 82, 14, 73, }}},
		{49,{51,{ 19, 73, 8, 2, 82, 14, 6, }}},
		{50,{69,{ 74, 22, 82, 6, }}},
		{51,{74,{ 10, 72, }}},
		{52,{72,{ 4, 10, }}},
		{53,{72,{ }}},
		{54,{75,{ 1, 2, 10, 14, 6, }}},
		{55,{76,{ 3, 6, }}},
		{56,{78,{ 9, 70, }}},
		{57,{70,{ 6, }}},
		{58,{70,{ 82, 6, }}},
		{59,{82,{ 84, 77, }}},
		{60,{77,{ 38, 84, 77, }}},
		{61,{77,{ }}},
		{62,{84,{ 86, 79, }}},
		{63,{79,{ 39, 86, 79, }}},
		{64,{79,{ }}},
		{65,{86,{ 88, 83, }}},
		{66,{83,{ 36, 88, 83, }}},
		{67,{83,{ 44, 88, 83, }}},
		{68,{83,{ }}},
		{69,{88,{ 92, 80, }}},
		{70,{80,{ 43, 92, 80, }}},
		{71,{80,{ 41, 92, 80, }}},
		{72,{80,{ 47, 92, 80, }}},
		{73,{80,{ 34, 92, 80, }}},
		{74,{80,{ }}},
		{75,{92,{ 42, 90, }}},
		{76,{90,{ 23, 42, 90, }}},
		{77,{90,{ 20, 42, 90, }}},
		{78,{90,{ }}},
		{79,{42,{ 91, 87, }}},
		{80,{87,{ 21, 91, 87, }}},
		{81,{87,{ 27, 91, 87, }}},
		{82,{87,{ }}},
		{83,{91,{ 37, 91, }}},
		{84,{91,{ 93, }}},
		{85,{93,{ 2, 82, 14, }}},
		{86,{93,{ 31, }}},
		{87,{93,{ 10, 89, }}},
		{88,{93,{ 24, }}},
		{89,{89,{ 2, 94, 14, }}},
		{90,{89,{ 4, 10, }}},
		{91,{89,{ }}},
		{92,{94,{ 81, }}},
		{93,{94,{ }}},
		{94,{81,{ 65, 85, }}},
		{95,{85,{ 7, 65, 85, }}},
		{96,{85,{ }}},
		{97,{65,{ 82, }}},
		{98,{73,{ 15, 63, 12, }}},
		{99,{73,{ 64, }}},
	};

	int start=94;
};
struct LLTable{
	std::map<NoTerm, std::map<Token, int>> LLtable = {
		{declaraciones, {{ESTRUCTURA,1},{VACIO,1},{ENTERO,1},{FLOTANTE,1},{CHAR,1},{NUM_DOBLE,1},{ENDF, 2},}},
		{declaracion, {{ESTRUCTURA,4},{VACIO,5},{ENTERO,3},{FLOTANTE,3},{CHAR,3},{NUM_DOBLE,3},}},
		{declaracion1, {{PUNTO_COMA,6},{COMA,6},{PAR_IZQ,7},}},
		{declaracion2, {{IDENTIFICADOR,8},{LLAVE_IZQ,9},}},
		{declaracion3, {{IDENTIFICADOR,11},{LLAVE_IZQ,10},}},
		{tipo, {{ENTERO,13},{FLOTANTE,14},{CHAR,12},{NUM_DOBLE,15},}},
		{lista_var, {{IDENTIFICADOR,17},}},
		{lista_var_, {{PUNTO_COMA,19},{COMA,18},}},
		{body_struct, {{LLAVE_IZQ,16},}},
		{lista_args, {{PAR_DER,21},{ENTERO,20},{FLOTANTE,20},{CHAR,20},{NUM_DOBLE,20},}},
		{args, {{ENTERO,22},{FLOTANTE,22},{CHAR,22},{NUM_DOBLE,22},}},
		{args_, {{COMA,23},{PAR_DER,24},}},
		{arg, {{ENTERO,25},{FLOTANTE,25},{CHAR,25},{NUM_DOBLE,25},}},
		{decl_locales, {{DEVUELVE,27},{IDENTIFICADOR,27},{LLAVE_DER,27},{SI,27},{MIENTRAS,27},{HACER,27},{INTERRUMPE,27},{ENTERO,26},{FLOTANTE,26},{CHAR,26},{NUM_DOBLE,26},{IMPRIME,27},{ESCANER,27},}},
		{decl_local, {{ENTERO,28},{FLOTANTE,28},{CHAR,28},{NUM_DOBLE,28},}},
		{bloque_sentencias, {{DEVUELVE,29},{IDENTIFICADOR,29},{LLAVE_DER,30},{SI,29},{MIENTRAS,29},{HACER,29},{INTERRUMPE,29},{IMPRIME,29},{ESCANER,29},}},
		{sentencias, {{DEVUELVE,31},{IDENTIFICADOR,31},{SI,31},{MIENTRAS,31},{HACER,31},{INTERRUMPE,31},{IMPRIME,31},{ESCANER,31},}},
		{sentencias_, {{DEVUELVE,32},{IDENTIFICADOR,32},{LLAVE_DER,33},{SI,32},{MIENTRAS,32},{HACER,32},{INTERRUMPE,32},{IMPRIME,32},{ESCANER,32},}},
		{sentencia, {{DEVUELVE,39},{IDENTIFICADOR,36},{SI,34},{MIENTRAS,35},{HACER,38},{INTERRUMPE,37},{IMPRIME,41},{ESCANER,40},}},
		{sentencia1, {{IDENTIFICADOR,43},{PAR_IZQ,43},{NUMERO,43},{CARACTERES,42},{CARACTER,43},{NEGACION,43},}},
		{sentIf, {{SI,44},}},
		{sentWhile, {{MIENTRAS,47},}},
		{sentDo, {{HACER,48},}},
		{sentAsig, {{IDENTIFICADOR,49},}},
		{sentIf_, {{DEVUELVE,46},{IDENTIFICADOR,46},{LLAVE_DER,46},{SI,46},{SINO,46},{MIENTRAS,46},{HACER,46},{INTERRUMPE,46},{IMPRIME,46},{ESCANER,46},}},
		{parte_izq, {{IDENTIFICADOR,50},}},
		{parte_izq_, {{PUNTO,51},{IGUAL,52},}},
		{sentScan, {{ESCANER,53},}},
		{sentBreak, {{INTERRUMPE,54},}},
		{sentReturn, {{DEVUELVE,55},}},
		{sentReturn_, {{PUNTO_COMA,56},{IDENTIFICADOR,57},{PAR_IZQ,57},{NUMERO,57},{CARACTER,57},{NEGACION,57},}},
		{expresion, {{IDENTIFICADOR,58},{PAR_IZQ,58},{NUMERO,58},{CARACTER,58},{NEGACION,58},}},
		{expresion_, {{PUNTO_COMA,60},{COMA,60},{PAR_DER,60},{DISYUNCION,59},}},
		{expresion1, {{IDENTIFICADOR,61},{PAR_IZQ,61},{NUMERO,61},{CARACTER,61},{NEGACION,61},}},
		{expresion1_, {{PUNTO_COMA,63},{COMA,63},{PAR_DER,63},{DISYUNCION,63},{CONJUNCION,62},}},
		{expresion2, {{IDENTIFICADOR,64},{PAR_IZQ,64},{NUMERO,64},{CARACTER,64},{NEGACION,64},}},
		{expresion2_, {{PUNTO_COMA,67},{COMA,67},{PAR_DER,67},{DISYUNCION,67},{CONJUNCION,67},{IGUALDAD,65},{DIFERENTE,66},}},
		{expresion3, {{IDENTIFICADOR,68},{PAR_IZQ,68},{NUMERO,68},{CARACTER,68},{NEGACION,68},}},
		{expresion3_, {{PUNTO_COMA,73},{COMA,73},{PAR_DER,73},{DISYUNCION,73},{CONJUNCION,73},{IGUALDAD,73},{DIFERENTE,73},{MAYOR,70},{MENOR,69},{MAYOR_IGUAL,72},{MENOR_IGUAL,71},}},
		{expresion4, {{IDENTIFICADOR,74},{PAR_IZQ,74},{NUMERO,74},{CARACTER,74},{NEGACION,74},}},
		{expresion4_, {{PUNTO_COMA,77},{COMA,77},{PAR_DER,77},{MAS,75},{MENOS,76},{DISYUNCION,77},{CONJUNCION,77},{IGUALDAD,77},{DIFERENTE,77},{MAYOR,77},{MENOR,77},{MAYOR_IGUAL,77},{MENOR_IGUAL,77},}},
		{expresion5, {{IDENTIFICADOR,78},{PAR_IZQ,78},{NUMERO,78},{CARACTER,78},{NEGACION,78},}},
		{expresion5_, {{PUNTO_COMA,81},{COMA,81},{PAR_DER,81},{MAS,81},{MENOS,81},{MULTIPLICACION,79},{DIVISION,80},{DISYUNCION,81},{CONJUNCION,81},{IGUALDAD,81},{DIFERENTE,81},{MAYOR,81},{MENOR,81},{MAYOR_IGUAL,81},{MENOR_IGUAL,81},}},
		{expresion6, {{IDENTIFICADOR,83},{PAR_IZQ,83},{NUMERO,83},{CARACTER,83},{NEGACION,82},}},
		{expresion7, {{IDENTIFICADOR,86},{PAR_IZQ,84},{NUMERO,85},{CARACTER,87},}},
		{expresion7_, {{PUNTO_COMA,90},{COMA,90},{PUNTO,89},{PAR_IZQ,88},{PAR_DER,90},{MAS,90},{MENOS,90},{MULTIPLICACION,90},{DIVISION,90},{DISYUNCION,90},{CONJUNCION,90},{IGUALDAD,90},{DIFERENTE,90},{MAYOR,90},{MENOR,90},{MAYOR_IGUAL,90},{MENOR_IGUAL,90},}},
		{lista_params, {{IDENTIFICADOR,91},{PAR_IZQ,91},{PAR_DER,92},{NUMERO,91},{CARACTER,91},{NEGACION,91},}},
		{params, {{IDENTIFICADOR,93},{PAR_IZQ,93},{NUMERO,93},{CARACTER,93},{NEGACION,93},}},
		{params_, {{COMA,94},{PAR_DER,95},}},
		{param, {{IDENTIFICADOR,96},{PAR_IZQ,96},{NUMERO,96},{CARACTER,96},{NEGACION,96},}},
		{bloque_o_sentencia, {{DEVUELVE,98},{IDENTIFICADOR,98},{LLAVE_IZQ,97},{SI,98},{MIENTRAS,98},{HACER,98},{INTERRUMPE,98},{IMPRIME,98},{ESCANER,98},}},
		{programa, {{ESTRUCTURA,0},{VACIO,0},{ENTERO,0},{FLOTANTE,0},{CHAR,0},{NUM_DOBLE,0},{ENDF, 0},}},
	};

};
class ObjPointer{
private:
	void *obj;
	std::string type;
public:
	ObjPointer(){
		obj = nullptr;
	}

	~ObjPointer(){
		delete obj;
	}

	ObjPointer(void *obj, std::string type){
		this->obj = obj;
		this->type = type;
	}

	void* getObject(){
		return obj;
	}

	std::string getType(){
		return type;
	}

};


class LLValueStack{
private:
	std::vector<ObjPointer> values;
public:
	ObjPointer top(){
		int sp = values.size() -1;
		return values[sp];
	}

	ObjPointer pop(){
		ObjPointer sp = top();
		values.pop_back();
		return sp;
	}

	ObjPointer operator[](int i){
		int sp = values.size() -1;
		sp -= i;
		return values[sp];
	}

	void push(ObjPointer obj)
	{
		values.push_back(obj);
	}
};


class LLParser
{
private:
	LLGrammar g;
	Lexer *lexer;
	Driver *driver =new Driver();
	std::stack<Expresion*> pilaAux; //Pila de Expresiones para heredar.

	LLTable tab;
	LLValueStack llvalues;
	Token token;
	ObjPointer llval;
	virtual void executeAction(int num);
public:
	LLParser()=default;
	LLParser(Lexer *lexer);
	~LLParser();
	int parse();
	Token eat();
	virtual void llacc(std::string);
	virtual void llerror(std::string);
};
LLParser::LLParser(Lexer *lexer)
{
	this->lexer = lexer;
}

LLParser::~LLParser()
{}
Token LLParser::eat(){
	Token token = (Token) lexer->yylex();
	if(token == IDENTIFICADOR)
		pilaAux.push(new Expresion(lexer->YYText()));
	else if(token == NUMERO)
		pilaAux.push(new Expresion(lexer->getType(),lexer->YYText()));
	else if(token == CARACTERES)
		pilaAux.push(new Expresion(lexer->YYText()));
	return token;
	
}


void LLParser::executeAction(int num){
	Expresion* e1;
	Expresion* e2;
	std::string id,cadena;
	int tipo_x, tam;
	std::vector<int>* args;
	std::vector<int>* lista;
	SymTab* tsLocal;
	switch (num)
	{
	case 0:

	break;
	case 1:
		e1 = pilaAux.top();
		pilaAux.pop();
		tipo_x=e1->tipo;
		e2 = pilaAux.top(); 
		id=e2->id;
		pilaAux.pop();
		Expresion* declaracion1 = new Expresion(id,tipo_x);
		pilaAux.push(declaracion1);
	break;
	case 2: //agregar_simbolo(std::string id, int tipo, std::vector<int> args)
		e2 = pilaAux.top(); 
		id=e2->id;
		bool is_there = driver->getPilaTS().global()->find(id);
		if (!is_there) {
			driver->tipoRetorno = 0;
			driver->tieneRetorno = false;
			driver->gen_label("id");
			
			driver->crear_ambito();
		}else{
			driver->error_semantico("El id: "+id+" ya existe");
		}
	break;
	case 3:
		driver->destruir_ambito();
		e1 = pilaAux.top(); //bloque-sentencias
		pilaAux.pop();
		e1 = pilaAux.top(); //decl_locales
		pilaAux.pop();
		e1 = pilaAux.top(); //lista_args
		pilaAux.pop();
		args = e1->lista;
		e1 = pilaAux.top(); //id
		pilaAux.pop();
		id = e1->id;
		
		driver->agregar_simbolo(id,tipo_x,*args);
	
		if (driver->tieneRetorno) {
			driver->error_semantico("La funcion no debe de retornar nada");
		}
		
	break;
	case 4:
		e1=pilaAux.top();
		tipo_x= e1->tipo;
		pilaAux.push(new Expresion(tipo_x));
		id=e1->id;
		bool is_there = driver->getPilaTS().global()->find(id);
		
		if (!is_there){
			driver->agregar_simbolo(id,tipo_x,"variable");
		}else{
			driver->error_semantico("La variable ya esta definida");
		}
	
	break;
	case 5:
		e1= pilaAux.top();
		tipo_x=e1->tipo;
		driver->tipoRetorno=tipo;
		driver->tieneRetorno = false;
		driver->nuevaEtiqueta();
		driver->crear_ambito();
	break;
	case 6:
		driver->destruir_ambito();
		bool is_there = driver->getPilaTS().global()->find(id);
		e1 = pilaAux.top(); //bloque-sentencias
		pilaAux.pop();
		e1 = pilaAux.top(); //decl_locales
		pilaAux.pop();
		e1 = pilaAux.top(); //lista_args
		pilaAux.pop();
		args = e1->lista;
		
		if (!is_there){
			driver->agregar_simbolo(id,tipo_x,*args);
		}
		
		if (!driver->tieneRetorno){
			driver->error_semantico("La función debe retornar algo");
		}

	break;

	case 7:
		e1 = pilaAux.top();//id
		pilaAux.pop();
		pilaAux.push(e1);
	break;

	case 8:
		driver->crear_ambito();
	break;

	case 9:
		tsLocal = driver->getPilaTS().top();
		driver->destruir_ambito();
		int tam = driver->calcularTamanio(tsLocal);
		tipo_x = driver->addTipo("struct",tam,tsLocal);
		pilaAux.push(new Expresion(tipo_x));

	break;

	case 10:
		id = pilaAux.top()->id;//id
		
		bool is_there = driver->getPilaTS().global()->find(id);
		if(!is_there){
			driver->agregar_simbolo(id,-1,"struct");
		}else{
			driver->error_semantico("Ya existe un ID con nombre "+ id);
		}
		driver-> crear_ambito();
	break;

	case 11:
		tsLocal = driver->getPilaTS().top();
		driver->destruir_ambito();
		int tam = driver->calcularTamanio(tsLocal);
		tipo_x = driver->addTipo("struct",tam,tsLocal);
		pilaAux.push(new Expresion(tipo_x));
	break;

	case 12:
		id = pilaAux.top()->id;//id
		bool is_there = driver->getPilaTS().global()->find(id);
		if (is_there){
			tipo_x = driver->getPilaTS().global()->getType(id);
			string name_type = driver->getTypeTab().getNombre(tipo_x);
			if (name_type != "struct"){
				driver->error_semantico("El ID no representa una estructura");
			}
		}else{
			driver->error_semantico("El ID no existe");
		}
		driver->tipoRetorno = tipo_x;
		driver->tieneRetorno = false;
		
	break;

	case 13:
		e1= pilaAux.top();// lista_args
		pilaAux.pop();
		e2= pilaAux.top();// id
		pilaAux.pop();
		id=e2->id;
		args=e1->lista;
		driver->gen_label("id");
		id = pilaAux.top()->id;//id

		bool is_there = driver->getPilaTS().global()->find(id);
		
		if(!is_there){
			driver->agregar_simbolo(id,driver->tipoRetorno,*args);
		}
		driver->crear_ambito();
	break;

	case 14:

		driver->destruir_ambito();
		bool retorno = driver->tieneRetorno;
		if (!retorno) {
			driver->error_semantico("La funcion debe retornar algo");			
		}
	break;
	
	case 15:  case 16: 
		// lista_var’.type = lista_var.type
		id = pilaAux.top()->id;
		pilaAux.pop();
		tipo_x = pilaAux.top()->tipo;

		bool is_there = driver->getPilaTS().global()->find(id);
		if (!is_there){
			driver->agregar_simbolo(id,tipo_x,"variable");
		}else{
			driver->error_semantico("Variable ya definida");
		}

	break;

	case 17: 
		tipo_x = 1;
		pilaAux.push(new Expresion(tipo_x));
	break;
	case 18: 
		tipo_x = 2;
		pilaAux.push(new Expresion(tipo_x));
	break;
	case 19: 
		tipo_x = 3;
		pilaAux.push(new Expresion(tipo_x));
	break;
	
	case 20:
		tipo_x = 4;
		pilaAux.push(new Expresion(tipo_x));
	break;
	
	case 22:
		pilaAux.top()->lista->clear();
	break;
	
	case 23: 
		tipo_x=pilaAux.top()->tipo;
		args = new vector<int>();	
		args->push_back(tipo_x);
		pilaAux.push(new Expresion(args));
	break;

	case 25: 
		tipo_x= pilaAux.top()->tipo;
		pilaAux.pop();
		lista = pilaAux.top()->lista;
		pilaAux.pop();
		lista->push_back(tipo_x);

		pilaAux.push(new Expresion(lista));
		
	break;
	
	case 28: 
		id= pilaAux.top()->id;
		pilaAux.pop();
		tipo_x = pilaAux.top()->tipo;
		if (driver->getPilaTS().global()->find(id))
		  driver->agregar_simbolo(id,tipo_x,"param");
		else
		   driver->error_semantico("Parametro ya definido");
		pilaAux.push(new Expresion(tipo_x));
	break;
	
	case 29:
		tipo_x = pilaAux.top()->tipo;
		pilaAux.pop();
		pilaAux.push(new Expresion(tipo_x));
	break;	
	case 30: 
		cadena=pilaAux.top()->id;
		driver->gen_imprimir(cadena);
		driver->addCadena(cadena);

	break;
	
	case 31:
		//se deja al lector
	break;

	default:
		break;
	}
}

int LLParser::parse(){
	std::stack<LLSymbol> llStack;
	std::map<Token, int>::iterator action;
	std::map<Token, int> row;
	std::vector<int> body;
	LLSymbol X;
	llStack.push({"$", "", ll_terminal, ENDF});
	llStack.push({"programa", "", ll_noterminal, programa});
	X = llStack.top();
	while(X.idx != 0){
		if(X.type == ll_action){
			executeAction(X.idx);
			llStack.pop();
		}else if(X.type == ll_terminal){
			if( X.idx == token){
				llStack.pop();
				token = eat();
			}else
				llerror("Error se sintaxis se esperaba el token X.name pero llego ");
		}else if(X.type == ll_noterminal){
			row = tab.LLtable[(NoTerm)X.idx];
			action = row.find(token);
			if(action != row.end()){
				body = g.prods[action->second].body;
				llStack.pop();
				for(std::vector<int>::reverse_iterator sym = body.rbegin(); sym != body.rend(); sym++){
					llStack.push(g.ll_symbols[*sym]);
				}
			}else
				llerror("Error de sintaxis llego el token ");
		}
	}
	if(token == 0){
		llacc("la cadena aceptada");
		return 0;
	}
	else{
		llerror("Se esperaba el fin de archivo");
	}
}


