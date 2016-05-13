#include<iostream>
#include "error.h"
#include "variable.h"
#include"assign_statement.h"

void Assign_stmt::execute(){
	switch(op){
		case 0:
			if(lhs->get_type()&INT){
				lhs->set(rhs->eval_int());
			}
			else if(lhs->get_type()&DOUBLE){
				lhs->set(rhs->eval_double());
			}
			else if(lhs->get_type()&STRING){
				lhs->set(rhs->eval_string());
			}
			else if(lhs->get_type()&ANIMATION_BLOCK){
				lhs->set(rhs->eval_animation_block());
			}
			break;
		case 1:
			if(lhs->get_type()&INT){
				lhs->set(lhs->get_int_value()+rhs->eval_int());
			}
			else if(lhs->get_type()&DOUBLE){
				lhs->set(lhs->get_double_value()+rhs->eval_double());
			}
			else if(lhs->get_type()&STRING){
				lhs->set(lhs->get_string_value()+rhs->eval_string());
			}
			break;
		case 2:
			if(lhs->get_type()&INT){
				lhs->set(lhs->get_int_value()-rhs->eval_int());
			}
			else if(lhs->get_type()&DOUBLE){
				lhs->set(lhs->get_double_value()-rhs->eval_double());
			}
			else if(lhs->get_type()&STRING){
				assert(false);
			}
			break;
		default:
			assert(false);
	}
}