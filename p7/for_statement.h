#ifndef FOR_STATEMENT_H
#define FOR_STATEMENT_H
#include "statement.h"
#include "gpl_assert.h"
#include "expression.h"

class For_stmt : public Statement {
	public:
		For_stmt(Statement_block* initializer, Statement_block* incrementor, Statement_block* body, Expression* condition){init=initializer, inc=incrementor, bod=body, cond=condition;}
		void execute();
		Statement_block* init;
		Statement_block* inc;
		Statement_block* bod;
		Expression* cond;
};
#endif