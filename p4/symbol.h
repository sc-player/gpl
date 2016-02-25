#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <iostream>
#include "gpl_type.h"

class Symbol{
    public:
	Symbol(int i, std::string n);
	Symbol(double d, std::string n);
	Symbol(std::string s, std::string n);
	Symbol(std::string n, Gpl_type t, int sz);
	Gpl_type type;
	void* package;
	std::string name;
	int size;
	void print(std::ostream& os);
};
#endif