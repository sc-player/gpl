#include "variable.h"
#include "expression.h"
#include "gpl_type.h"

Variable::Variable(Symbol* symb){ 
	sym=symb; 
	type=symb->get_type();
}

Variable::Variable(Symbol* symb, Expression* expre){
	sym=symb; 
	size=expre; 
	type=symb->get_type();
}

Variable::Variable(Symbol* symb, std::string parameter){
	sym=symb; 
	param=parameter; 
	sym->get_game_object_value()->get_member_variable_type(param, type);
}

Variable::Variable(Symbol*symb, std::string parameter, Expression* exp){
	sym=symb;
	param=parameter;
	sym->get_game_object_value()->get_member_variable_type(param, type);
	memberSize=exp;
}

int Variable::get_int_value(){
	int res;
	if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else
	{
		return sym->get_int_value();
	}
}
double Variable::get_double_value(){
	double res;
	if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else
	{
		return sym->get_double_value();
	}
}
std::string Variable::get_string_value(){
	std::string res;
	if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else
	{
		return sym->get_string_value();
	}
}
Animation_block* Variable::get_animation_block_value(){
	Animation_block* res;
	if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else
	{
		return sym->get_animation_block_value();
	}
}
