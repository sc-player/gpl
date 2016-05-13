#include "variable.h"
#include "expression.h"
#include "gpl_type.h"
#include "error.h"
#include <string>

Variable::Variable(Symbol* symb){ 
	sym=symb; 
	type=symb->get_type();
}

Variable::Variable(Symbol* symb, Expression* expre){
	sym=symb; 
	index=expre; 
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
	index=exp;
}

int Variable::get_int_value(){
	int res;
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if(index->eval_int()>sym->get_size()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			return sym->get_int_value(0);
		}
		sym->get_game_object_value(index->eval_int())->get_member_variable(param, res);
		return res;
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else if(sym->get_type()&ARRAY){
		if(index->eval_int()>sym->get_size()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			return sym->get_int_value(0);
		}
		return sym->get_int_value(index->eval_int());
	}
	else
	{
		return sym->get_int_value();
	}
}
double Variable::get_double_value(){
	double res;
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if(index->eval_int()>sym->get_size()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			return sym->get_double_value(0);
		}
		sym->get_game_object_value(index->eval_int())->get_member_variable(param, res);
		return res;
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else if(sym->get_type()&ARRAY){
		if(index->eval_int()>sym->get_size()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			return sym->get_double_value(0);
		}
		return sym->get_double_value(index->eval_int());
	}
	else
	{
		return sym->get_double_value();
	}
}
std::string Variable::get_string_value(){
	std::string res;
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if(index->eval_int()>sym->get_size()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			return sym->get_string_value(0);
		}
		sym->get_game_object_value(index->eval_int())->get_member_variable(param, res);
		return res;
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else if(sym->get_type()&ARRAY){
		if(index->eval_int()>sym->get_size()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			return sym->get_string_value(0);
		}
		return sym->get_string_value(index->eval_int());
	}
	else
	{
		return sym->get_string_value();
	}
}
Animation_block* Variable::get_animation_block_value(){
	Animation_block* res;
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if(index->eval_int()>sym->get_size()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->get_game_object_value(0)->get_member_variable(param, res);
			return res;
		}
		sym->get_game_object_value(index->eval_int())->get_member_variable(param, res);
		return res;
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->get_member_variable(param, res);
		return res;
	}
	else
	{
		return sym->get_animation_block_value();
	}
}
void Variable::set(int i){
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if((index->eval_int()>sym->get_size())||(index->eval_int()<0)){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->get_game_object_value(0)->set_member_variable(param, i);
		}
		else sym->get_game_object_value(index->eval_int())->set_member_variable(param, i);
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->set_member_variable(param, i);
	}
	else if(sym->get_type()&ARRAY){
		if((index->eval_int()>sym->get_size())||(index->eval_int()<0)){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->set(i, 0);
		}
		else sym->set(i, index->eval_int());
	}
	else{
		sym->set(i);
	}
}
void Variable::set(double d){
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if((index->eval_int()>sym->get_size())||(index->eval_int()<0)){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->get_game_object_value(0)->set_member_variable(param, d);
		}
		else sym->get_game_object_value(index->eval_int())->set_member_variable(param, d);
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->set_member_variable(param, d);
	}
	else if(sym->get_type()&ARRAY){
		if((index->eval_int()>sym->get_size())||(index->eval_int()<0)){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->set(d, 0);
		}
		else sym->set(d, index->eval_int());
	}
	else{
		sym->set(d);
	}
}
void Variable::set(std::string s){
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if((index->eval_int()>sym->get_size())||(index->eval_int()<0)){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->get_game_object_value(0)->set_member_variable(param, s);
		}
		else sym->get_game_object_value(index->eval_int())->set_member_variable(param, s);
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->set_member_variable(param, s);
	}
	else if(sym->get_type()&ARRAY){
		if((index->eval_int()>sym->get_size())||(index->eval_int()<0)){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->set(s, 0);
		}
		else sym->set(s, index->eval_int());
	}
	else{
		sym->set(s);
	}
}
void Variable::set(Animation_block* a){
	if((sym->get_type()&GAME_OBJECT)&&(sym->get_type()&ARRAY)){
		if((index->eval_int()>sym->get_size())||(index->eval_int()<0)){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, sym->get_name(), std::to_string(index->eval_int())); 
			sym->get_game_object_value(0)->set_member_variable(param, a);
		}
		else sym->get_game_object_value(index->eval_int())->set_member_variable(param, a);
	}
	else if(sym->get_type()&GAME_OBJECT){
		sym->get_game_object_value()->set_member_variable(param, a);
	}
	else{
		sym->set(a);
	}
}
