#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <iostream>
#include "game_object.h"
#include "gpl_type.h"
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "textbox.h"
#include "pixmap.h"
#include "animation_block.h"

class Symbol{
    private:
	Gpl_type type;
	void* package;
	std::string name;
	int size;
    public:
	Symbol(int i, std::string n);
	Symbol(double d, std::string n);
	Symbol(std::string s, std::string n);
	Symbol(std::string n, Gpl_type t, int sz);
	Symbol(Game_object* g, Gpl_type t, std::string n);
	Symbol(Animation_block* a, std::string n);
	Gpl_type get_type() {return type; }
	int get_int_value(){ return *(int*)package; }
	double get_double_value(){return *(double*)package;}
	std:: string get_string_value(){return *(std::string*)package;}
	int get_int_value(int index){return ((int*)package)[index];}
	double get_double_value(int index){return ((double*)package)[index];}
	std::string get_string_value(int index){return ((std::string*)package)[index];}
	Game_object* get_game_object_value(){return (Game_object*)package;}
	Game_object* get_game_object_value(int index);
	Animation_block* get_animation_block_value(){return (Animation_block*)package;}
	std:: string get_name(){return name;}
	int get_size(){return size;}
	bool is_game_object(){ return (type&GAME_OBJECT)? true:false; }
	void print(std::ostream& os);
	void set(int i){*(int*)package=i;}
	void set(double d){*(double*)package=d;}
	void set(std::string s){*(std::string*)package=s;}
	void set(Animation_block* a){package=a;}
	void set(int i, int index){((int*)package)[index]=i;}
	void set(double d, int index){((double*)package)[index]=d;}
	void set(std::string s, int index){((std::string*)package)[index]=s;}
	void set(Game_object*g){package=g;}
};
#endif
