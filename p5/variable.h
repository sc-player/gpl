#ifndef VARIABLE_H
#define VARIABLE_H
#include "expression.h"
#include <string>

class Expression;

class Variable{
	public:
		Variable(Symbol* symb){ sym=symb; }
		Variable(Symbol* symb, Expression* expre){sym=symb; expr=expre;}
		Symbol* sym;
		Expression* expr;
		Gpl_type get_type(){return sym->type;}
		int get_int_value(){ return *(int*) sym->package;}
		double get_double_value(){return *(double*) sym->package;}
		std::string get_string_value(){return *(std::string*) sym->package;}
};
#endif