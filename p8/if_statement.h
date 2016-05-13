#ifndef IF_STATEMENT_H
#define IF_STATEMENT_H
#include "statement.h"
#include "gpl_assert.h"
#include "expression.h"

class If_stmt : public Statement {
	public:
		If_stmt(Expression* condition, Statement_block* True, Statement_block* False){cond=condition, then=True, Else=False;}
		void execute();
		Expression* cond;
		Statement_block* then;
		Statement_block* Else;
};
#endif