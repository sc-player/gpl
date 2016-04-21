#ifndef ASSIGN_STATEMENT_H
#define ASSIGN_STATEMENT_H
#include "statement.h"
#include "gpl_assert.h"
#include "expression.h"

class Assign_stmt : public Statement {
	public:
		Assign_stmt(Variable* LHS, Expression* RHS, int operType){lhs=LHS; rhs=RHS; op=operType;}
		void execute();
		int op;
		Expression * rhs;
		Variable* lhs;
};
#endif