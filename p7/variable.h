#ifndef VARIABLE_H
#define VARIABLE_H
#include "gpl_type.h"
#include "symbol.h"
#include "animation_block.h"
#include <string>

class Expression;

class Variable{
	public:
		Variable(Symbol* symb);
		Variable(Symbol* symb, Expression* expre);
		Variable(Symbol* symb, std::string parameter);
		Variable(Symbol* symb, std::string parameter, Expression* expr);
		Symbol* sym;
		Expression* index;
		Expression* memberIndex;
		std::string param;
		Gpl_type type;
		Gpl_type get_type(){return type;}
		int get_int_value();
		double get_double_value();
		std::string get_string_value();
		std::string get_name(){return sym->get_name();}
		Animation_block* get_animation_block_value();
		void set(int i);
		void set(double d);
		void set(std::string s);
};
#endif
