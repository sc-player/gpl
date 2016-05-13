// updated 2/14/16

/***
  This file is a placeholder for the Statement_block class you will write in 
  the next assignment p7.

  You may use it w/o modification in p6.

  You may use it as a starting point for your Statement_block class for p7.

  I have put in just enough for it to work in p6.

***/


#ifndef STATEMENT_BLOCK_H
#define STATEMENT_BLOCK_H

#include <iostream>
#include <vector>
#include "statement.h"

class Game_object;

class Statement_block
{
  public:
    Statement_block();
    std::vector<Statement*> stateVec;
    void execute();
};

#endif // #ifndef STATEMENT_BLOCK_H
