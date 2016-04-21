#include<iostream>
#include "error.h"
#include "variable.h"
#include "for_statement.h"

void For_stmt::execute(){
	for(init->execute(); cond->eval_int(); inc->execute()){
		bod->execute();
	}
}