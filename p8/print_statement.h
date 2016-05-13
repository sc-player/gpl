#ifndef PRINT_STATEMENT_H
#define PRINT_STATEMENT_H
#include "statement.h"
#include "expression.h"

class Print_stmt : public Statement {
	public:
		Print_stmt(Expression* exp, int line){line_num=line; expr=exp;}
		void execute();
		int line_num;
		Expression * expr;
};
#endif