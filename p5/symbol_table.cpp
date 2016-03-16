#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include "symbol_table.h"
#include "symbol.h"
#include "error.h"

bool lessThan (Symbol* i,Symbol* j) { return (i->name<j->name); }
Symbol_table* Symbol_table::m_instance;

Symbol_table* Symbol_table::instance(){
	if(m_instance==0) m_instance= new Symbol_table();
	return m_instance;
}

Symbol* Symbol_table::lookup(std::string name){
	if(sTable.find(name)!=sTable.end()) return sTable[name];
	return NULL;
}

void Symbol_table::print(std::ostream &os){
	std::vector<Symbol*> printVec;
	for(auto it=sTable.begin(); it!=sTable.end(); ++it)
		printVec.push_back(it->second);
	std::sort(printVec.begin(), printVec.end(), lessThan);
	for(unsigned i=0; i<printVec.size(); ++i)
		printVec[i]->print(os);
}

void Symbol_table::addSymbol(Symbol * sym){
	if(lookup(sym->name)==NULL){
		sTable.insert({sym->name, sym});
		return;
	}
	else{
		Error::error(Error::PREVIOUSLY_DECLARED_VARIABLE, sym->name);
	}
}