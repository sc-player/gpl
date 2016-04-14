#include <iostream>
#include <stdio.h>
#include <string.h>
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "textbox.h"
#include "pixmap.h"
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

Symbol::Symbol(Game_object* g, Gpl_type t, std::string n){
	package = g;
	type=t;
	name=n;
	size=INT_MIN;
}

Symbol::Symbol(Animation_block* a, std::string n){
	package=a;
	name=n;
	type=ANIMATION_BLOCK;
	size=INT_MIN;
}

Symbol::Symbol(std::string n, Gpl_type t, int sz){
	switch(t){
		case INT_ARRAY:
			package=new int[sz];
			for(int i=0; i<sz; ++i){
				((int*)package)[i]=0;
			}
			break;
		case DOUBLE_ARRAY:
			package=new double[sz];
			for(int i=0; i<sz; ++i)
				((double*)package)[i]=0.0;
			break;
		case STRING_ARRAY:	
			package=new std::string[sz];
			for(int i=0; i<sz; ++i)
				((std::string *)package)[i]="";
			break;
		case RECTANGLE_ARRAY:
			package= new Rectangle[sz];
			break;
		case TRIANGLE_ARRAY:
			package=new Triangle[sz];
			break;
		case CIRCLE_ARRAY:
			package=new Circle[sz];
			break;
		case TEXTBOX_ARRAY:
			package=new Textbox[sz];
			break;
		case PIXMAP_ARRAY:
			package=new Pixmap[sz];
			break;
		default:
			break;
	}
	name=n;
	type=t;
	size=sz;
}

void Symbol::print(std::ostream& os){
	Gpl_type testType=type;
	if((testType==RECTANGLE) || (testType==TRIANGLE) || (testType==CIRCLE) || (testType==TEXTBOX) || (testType==PIXMAP)){
		testType=GAME_OBJECT;
	}
	switch(testType){
		case INT:
			os << "int " << name << " = " << *(int*)package << "\n";
			break;
		case DOUBLE:
			os << "double " << name << " = " << *(double*)package << "\n";
			break;
		case STRING:
			os << "string " << name << " = \"" << *(std::string*)package << "\"\n";
			break;
		case ANIMATION_BLOCK:
			os << "animation_block " << name << std::endl;
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
		case GAME_OBJECT:
			Game_object* g;
			g=get_game_object_value();
			g->print(get_name(), os);
			break;
		case TRIANGLE_ARRAY:
			for(int i=0; i<size; ++i){
				((Triangle*)package)[i].print(name+"["+std::to_string(i)+"]", os);
			}
			break;
		case RECTANGLE_ARRAY:
			for(int i=0; i<size; ++i){
				((Rectangle*)package)[i].print(name+"["+std::to_string(i)+"]", os);
			}
			break;
		case CIRCLE_ARRAY:
			for(int i=0; i<size; ++i){
				((Circle*)package)[i].print(name+"["+std::to_string(i)+"]", os);
			}
			break;
		case TEXTBOX_ARRAY:
			for(int i=0; i<size; ++i){
				((Textbox*)package)[i].print(name+"["+std::to_string(i)+"]", os);
			}
			break;
		case PIXMAP_ARRAY:
			for(int i=0; i<size; ++i){
				((Pixmap*)package)[i].print(name+"["+std::to_string(i)+"]", os);
			}
			break;
		default:
			break;
	}
}
