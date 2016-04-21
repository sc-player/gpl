#include<iostream>
#include "error.h"
#include "variable.h"
#include "if_statement.h"

void If_stmt::execute(){
	if(cond->eval_int()){
		then->execute();
	}
	else if(Else){
		Else->execute();
	}
}