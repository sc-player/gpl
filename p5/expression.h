#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include "gpl_type.h"
#include "symbol_table.h"
#include "variable.h"

class Variable;

class Expression{
	private:
		enum KINDS{EXPRESSION, CONSTANT, VARIABLE};
		Expression* left, *right;
		int Int;
		double Double;
		std::string String;
		Variable* var;
		Operator_type op;
		Gpl_type type;
		KINDS kind;
	public:
		Expression(int i){Int=i; left=right=NULL; type=INT; kind=CONSTANT;}
		Expression(double d){Double=d; left=right=NULL; type=DOUBLE; kind=CONSTANT;}
		Expression(std::string s){String=s; left=right=NULL; type=STRING; kind=CONSTANT;}
		Expression(Expression* l, Operator_type ope, Expression* r);
		Expression(Expression*l, Operator_type ope);
		Expression(Variable* v){var=v; left=right=NULL; type=var->get_type(); kind=VARIABLE;}
		int eval_int();
		double eval_double();
		std::string eval_string();
		Gpl_type get_type(){return type;}
};
#endif