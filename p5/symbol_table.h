#ifndef S_TABLE_H
#define S_TABLE_H
#include <string>
#include <unordered_map>
#include "symbol.h"

class Symbol_table{
    public:
	static Symbol_table* instance();
	Symbol* lookup(std::string name);
	void print(std::ostream &os);
	void addSymbol(Symbol* sym);
    private:
	static Symbol_table* m_instance;
	Symbol_table(){};
	Symbol_table(const Symbol_table&);
	const Symbol_table &operator=(const Symbol_table&);
	std::unordered_map<std::string, Symbol*> sTable;
};
#endif
