// updated 2/14/16

#include "statement_block.h"
#include "gpl_assert.h"
using namespace std;


Statement_block::Statement_block()
{

}

// this function is called for all non-animation_block statement_blocks
// Implement it for p7
void Statement_block::execute()
{
	for(unsigned int i=0; i<stateVec.size(); ++i){
		stateVec[i]->execute();
	}
}
