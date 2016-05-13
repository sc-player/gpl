#define _USE_MATH_DEFINES

#include "expression.h"
#include <string>
#include <cmath>
#include <sstream>
#include "gpl_assert.h"
#include "error.h"
#include "gpl_type.h"
#include "variable.h"

Expression::Expression(Expression* l, Operator_type ope, Expression* r){
	left=l;
	right=r;
	op=ope;
	kind=EXPRESSION;
	switch(op){
		case PLUS:
			if((left->type&STRING)||(right->type&STRING)) type=STRING;
			else if((left->type&DOUBLE)||(right->type&DOUBLE)) type=DOUBLE;
			else { type=INT; }
			break;
		case MINUS:
			if((left->type&DOUBLE)||(right->type&DOUBLE)) type=DOUBLE;
			else { type=INT; }
			break;
		case MULTIPLY:
			if((left->type&DOUBLE)||(right->type&DOUBLE)) type=DOUBLE;
			else { type=INT; }
			break;
		case DIVIDE:
			if((left->type&DOUBLE)||(right->type&DOUBLE)) type=DOUBLE;
			else { type=INT; }
			break;
		case MOD:
			type=INT;
			break;
		case AND:
			type=INT;
			break;
		case OR:
			type=INT;
			break;
		case EQUAL:
			type=INT;
			break;
		case NOT_EQUAL:
			type=INT;
			break;
		case LESS_THAN:
			type=INT;
			break;
		case LESS_THAN_EQUAL:
			type=INT;
			break;
		case GREATER_THAN:
			type=INT;
			break;
		case GREATER_THAN_EQUAL:
			type=INT;
			break;
		case TOUCHES:
			type=INT;
			break;
		case NEAR:
			type=INT;
			break;
		default: assert(false);
	}
}

Expression::Expression(Expression* l, Operator_type ope){
	left=l;
	op=ope;
	kind=EXPRESSION;
	switch(op){
		case NOT:
			type=INT;
			break;
		case UNARY_MINUS:
			if(l->type&DOUBLE) type=DOUBLE;
			else { type=INT; }
			break;
		case COS:
			type=DOUBLE;
			break;
		case SIN:
			type=DOUBLE;
			break;
		case TAN:
			type=DOUBLE;
			break;
		case ACOS:
			type=DOUBLE;
			break;
		case ASIN:
			type=DOUBLE;
			break;
		case ATAN:
			type=DOUBLE;
			break;
		case SQRT:
			type=DOUBLE;
			break;
		case ABS:
			if(l->type&DOUBLE) type=DOUBLE;
			else { type=INT; }
			break;
		case FLOOR:
			type=INT;
			break;
		case RANDOM:
			type=INT;
			break;
		default:
			assert(false);
	}
}

Expression::Expression(Variable* v){
	var=v; 
	left=right=NULL; 
	type=var->get_type(); 
	kind=VARIABLE;
}

int Expression::eval_int(){
	if(kind==CONSTANT) return Int;
	else if(kind==VARIABLE){
		return var->get_int_value();
	}
	else if(kind==EXPRESSION){
		switch(op){
			case PLUS:
				return left->eval_int()+right->eval_int();
				break;
			case MINUS:
				return left->eval_int()-right->eval_int();
				break;
			case MULTIPLY:
				return left->eval_int()*right->eval_int();
				break;
			case DIVIDE:
				if(right->eval_int()==0){
					Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
					return 0;
				}
				return left->eval_int()/right->eval_int();
				break;
			case MOD:
				if(right->eval_int()==0){
					Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
					return 0;
				}
				return left->eval_int()%right->eval_int();
				break;
			case UNARY_MINUS:
				return -(left->eval_int());
				break;
			case ABS:
				return abs(left->eval_int());
				break;
			case RANDOM:
				return rand()%left->eval_int();
				break;
			case FLOOR:
				if(left->type&DOUBLE) return floor(left->eval_double());
				else if(left->type&INT) return floor(left->eval_int());
				assert(false);
				break;
			case AND:
				if((left->type&DOUBLE)&&(right->type&DOUBLE)) return left->eval_double()&&right->eval_double();
				if((left->type&DOUBLE)&&(right->type&INT)) return left->eval_double()&&right->eval_int();
				if((left->type&INT)&&(right->type&DOUBLE)) return left->eval_int()&&right->eval_double();
				if((left->type&INT)&&(right->type&INT)) return left->eval_int()&&right->eval_int();
				assert(false);
				break;
			case OR:
				if((left->type&DOUBLE)&&(right->type&DOUBLE)) return left->eval_double()||right->eval_double();
				if((left->type&DOUBLE)&&(right->type&INT)) return left->eval_double()||right->eval_int();
				if((left->type&INT)&&(right->type&DOUBLE)) return left->eval_int()||right->eval_double();
				if((left->type&INT)&&(right->type&INT)) return left->eval_int()||right->eval_int();
				assert(false);
				break;
			case NOT:
				if(left->type&DOUBLE) return !(left->eval_double());
				if(left->type&INT) return !left->eval_int();
				assert(false);
				break;
			case EQUAL:
				if((left->type&STRING)||(right->type&STRING)) return left->eval_string() == right->eval_string();
				if((left->type&DOUBLE)||(right->type&DOUBLE)) return left->eval_double()==right->eval_double();
				if((left->type&INT)||(right->type&INT)) return left->eval_int() == right->eval_int();
				assert(false);
				break;
			case NOT_EQUAL:
				if((left->type&STRING)||(right->type&STRING)) return left->eval_string() != right->eval_string();
				if((left->type&DOUBLE)||(right->type&DOUBLE)) return left->eval_double()!=right->eval_double();
				if((left->type&INT)||(right->type&INT)) return left->eval_int() != right->eval_int();
				assert(false);
				break;
			case LESS_THAN:
				if((left->type&STRING)||(right->type&STRING)) return left->eval_string() < right->eval_string();
				if((left->type&DOUBLE)||(right->type&DOUBLE)) return left->eval_double() < right->eval_double();
				if((left->type&INT)||(right->type&INT)) return left->eval_int() < right->eval_int();
				assert(false);
				break;
			case GREATER_THAN:
				if((left->type&STRING)||(right->type&STRING)) return left->eval_string() > right->eval_string();
				if((left->type&DOUBLE)||(right->type&DOUBLE)) return left->eval_double() > right->eval_double();
				if((left->type&INT)||(right->type&INT)) return left->eval_int() > right->eval_int();
				assert(false);
				break;
			case LESS_THAN_EQUAL:
				if((left->type&STRING)||(right->type&STRING)) return left->eval_string() <= right->eval_string();
				if((left->type&DOUBLE)||(right->type&DOUBLE)) return left->eval_double() <=right->eval_double();
				if((left->type&INT)||(right->type&INT)) return left->eval_int() <= right->eval_int();
				assert(false);
				break;
			case GREATER_THAN_EQUAL:
				if((left->type&STRING)||(right->type&STRING)) return left->eval_string() >= right->eval_string();
				if((left->type&DOUBLE)||(right->type&DOUBLE)) return left->eval_double()>=right->eval_double();
				if((left->type&INT)||(right->type&INT)) return left->eval_int() >= right->eval_int();
				assert(false);
				break;
			case TOUCHES:
				if((left->type&ARRAY)&&(right->type&ARRAY)) return left->get_var()->sym->get_game_object_value(left->get_var()->index->eval_int())->touches(right->get_var()->sym->get_game_object_value(right->get_var()->index->eval_int()));
				if(left->type&ARRAY) return left->get_var()->sym->get_game_object_value(left->get_var()->index->eval_int())->touches(right->get_var()->sym->get_game_object_value());
				if(right->type&ARRAY) return left->get_var()->sym->get_game_object_value()->touches(right->get_var()->sym->get_game_object_value(right->get_var()->index->eval_int()));
				return left->get_var()->sym->get_game_object_value()->touches(right->get_var()->sym->get_game_object_value());
				break;
			case NEAR:
				if((left->type&ARRAY)&&(right->type&ARRAY)) return left->get_var()->sym->get_game_object_value(left->get_var()->index->eval_int())->near(right->get_var()->sym->get_game_object_value(right->get_var()->index->eval_int()));
				if(left->type&ARRAY) return left->get_var()->sym->get_game_object_value(left->get_var()->index->eval_int())->near(right->get_var()->sym->get_game_object_value());
				if(right->type&ARRAY) return left->get_var()->sym->get_game_object_value()->near(right->get_var()->sym->get_game_object_value(right->get_var()->index->eval_int()));
				return left->get_var()->sym->get_game_object_value()->near(right->get_var()->sym->get_game_object_value());
				break;
			default:
				assert(false);
		}
	}
	return 0;
}

double Expression::eval_double(){
	if(type&INT){
		int value=eval_int();
		double d=value;
		return d;
	}
	else if(type&DOUBLE){
		if(kind==CONSTANT) return Double;
		else if(kind==VARIABLE) return var->get_double_value();
		else if(kind==EXPRESSION){
			switch(op){
				case PLUS:
					return left->eval_double()+ right->eval_double();
					break;
				case MINUS:
					return left->eval_double()-right->eval_double();
					break;
				case MULTIPLY:
					return left->eval_double()*right->eval_double();
					break;
				case DIVIDE:
					if(!right->eval_double()){
						Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
						return 0;
					}
					return left->eval_double()/right->eval_double();
					break;
				case UNARY_MINUS:
					return -(left->eval_double());
					break;
				case COS:
					if(left->type&DOUBLE) return cos(left->eval_double()*M_PI/180.0);
					else if(left->type&INT) return cos(left->eval_int()*M_PI/180.0);
					assert(false);
					break;
				case SIN:
					if(left->type&DOUBLE) return sin(left->eval_double()*M_PI/180.0);
					else if(left->type&INT) return sin(left->eval_int()*M_PI/180.0);
					assert(false);
					break;
				case TAN:
					if(left->type&DOUBLE) return tan(left->eval_double()*M_PI/180.0);
					else if(left->type&INT) return tan(left->eval_int()*M_PI/180.0);
					assert(false);
					break;
				case ACOS:
					if(left->type&DOUBLE) return acos(left->eval_double())*180.0/M_PI;
					else if(left->type&INT) return acos(left->eval_int())*180.0/M_PI;
					assert(false);
					break;
				case ASIN:
					if(left->type&DOUBLE) return asin(left->eval_double())*180.0/M_PI;
					else if(left->type&INT) return asin(left->eval_int())*180.0/M_PI;
					assert(false);
					break;
				case ATAN:
					if(left->type&DOUBLE) return atan(left->eval_double())*180.0/M_PI;
					else if(left->type&INT) return atan(left->eval_int())*180.0/M_PI;
					assert(false);
					break;
				case SQRT:
					if(left->type&DOUBLE) return sqrt(left->eval_double());
					else if(left->type&INT) return sqrt(left->eval_int());
					assert(false);
					break;
				case ABS:
					if(left->type&DOUBLE) return fabs(left->eval_double());
					assert(false);
					break;
				default:
					assert(false);
			}
		}
	}
	return 0.0;
}

std::string Expression::eval_string(){
	if(type&INT){
		int value=eval_int();
		std::string s=std::to_string(value);
		return s;
	}
	else if(type&DOUBLE){
		std::stringstream ss;
		double value=eval_double();
		ss<<value;
		std::string s = ss.str();
		return s;
	}
	else if(type&STRING){
		if(kind==CONSTANT) return String;
		else if(kind==VARIABLE) return var->get_string_value();
		else if(kind==EXPRESSION){
			switch(op){
				case PLUS:
					return left->eval_string()+right->eval_string();
					break;
				default:
					assert(false);
					break;
			}
		}
	}
	return "";
}

Animation_block* Expression::eval_animation_block(){
	return var->get_animation_block_value();
}

std::string Expression::get_name(){
	std::string res;
	(kind==VARIABLE)? res=var->get_name():res="";
	if(res=="") assert(false);
	return res;
}