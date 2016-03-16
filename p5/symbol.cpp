#include <iostream>
#include <stdio.h>
#include <string.h>
#include "symbol.h"
#include "symbol_table.h"
#include "gpl_type.h"
#include <limits.h>

Symbol::Symbol(int i, std::string n){
	package=new int(i); 
	name=n; 
	type=INT;
	size=INT_MIN;
}

Symbol::Symbol(double d, std::string n){
	package=new double(d); 
	name=n; 
	type=DOUBLE;
	size=INT_MIN;
}

Symbol::Symbol(std::string s, std::string n){
	package=new std::string(s); 
	name=n; 
	type=STRING;
	size=INT_MIN;
}

Symbol::Symbol(std::string n, Gpl_type t, int sz){
	if(t==INT_ARRAY){
		package=new int[sz];
		for(int i=0; i<sz; ++i){
			((int*)package)[i]=0;
		}
	}
	else {
		if(t==DOUBLE_ARRAY){
			package=new double[sz];
			for(int i=0; i<sz; ++i)
				((double*)package)[i]=0.0;
		}
		else{
			if(t==STRING_ARRAY){	
				package=new std::string[sz];
				for(int i=0; i<sz; ++i)
					((std::string *)package)[i]="";
			}
		}
	}
	name=n;
	type=t;
	size=sz;
}

void Symbol::print(std::ostream& os){
	switch(type){
		case INT:
			os << "int " << name << " = " << *(int*)package << "\n";
			break;
		case DOUBLE:
			os << "double " << name << " = " << *(double*)package << "\n";
			break;
		case STRING:
			os << "string " << name << " = \"" << *(std::string*)package << "\"\n";
			break;
		case INT_ARRAY:
			for(int i=0; i<size; ++i){
				os << "int " << name << "[" <<i<<"] = "<< ((int*)package)[i] << std::endl;
			}
			break;
		case DOUBLE_ARRAY:
			for(int i=0; i<size; ++i){
				os << "double " << name << "[" <<i<<"] = "<< ((double*)package)[i] << std::endl;
			}
			break;
		case STRING_ARRAY:
			for(int i=0; i<size; ++i){
				os << "string " << name << "[" <<i<<"] = \""<< ((std::string*)package)[i] << "\"\n";
			}
			break;
		default:
			break;
	}
	
}