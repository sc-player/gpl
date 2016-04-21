#include<iostream>
#include "error.h"
#include "variable.h"
#include"exit_statement.h"

void Exit_stmt::execute(){
	std::cout << "gpl[" << line << "]: exit(" << exp->eval_int() << ")\n";
	exit(exp->eval_int());
}