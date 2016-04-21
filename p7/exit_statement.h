#ifndef EXIT_STATEMENT_H
#define EXIT_STATEMENT_H
#include "statement.h"
#include "gpl_assert.h"
#include "expression.h"

class Exit_stmt : public Statement {
	public:
		Exit_stmt(Expression* expr, int line_count){exp=expr; line=line_count;}
		void execute();
		Expression * exp;
		int line;
};
#endif