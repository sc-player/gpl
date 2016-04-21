#include<iostream>
#include"print_statement.h"

void Print_stmt::execute(){
	std::cout <<"print[" << line_num <<"]: " << expr->eval_string() << std::endl;
}