%{  // bison syntax to indicate the start of the header
    // the header is copied directly into y.tab.c (the generated parser)

extern int yylex();               // this lexer function returns next token
extern int yyerror(const char *); // used to print errors
extern int line_count;            // current line in the input; from record.l

#include "error.h"      // class for printing errors (used by gpl)
#include "parser.h"
#include "symbol_table.h"
#include "variable.h"
#include "symbol.h"
#include "gpl_type.h"
#include "animation_block.h"
#include "game_object.h"
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"
#include "pixmap.h"
#include "textbox.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

Game_object* cur_object_under_construction;
std::string cur_object_name;
// bison syntax to indicate the end of the header
%} 

// The union is used to declare the variable yylval which is used to
// pass data between the flex generated lexer and the bison generated parser, 
// and to pass values up/down the parse tree.
// 
// A union is kind of like a structure or class, but you can only use one 
// field at a time.  Each line describes one item in the union.  The left hand
// side is the type, the right hand side is a name for the type.
// 
// Unions do not have any error checking.  For example, if you put an int in
// the following union  (my_union.union_int = 42)  and then attempt to use it
// as a string (cout << my_union.union_string) you will get garbage.

// The "%union" is bison syntax
// The "union_" is my convention to indicate a member of the union 
//     (it can be hard to tell what is a union field and what is not)
//
// In this example, the union only has one member (union_int).  You will
// be adding a double declaration to the union.

%union {
 int            union_int;
 double	 union_double;
 std::string    *union_string;  // MUST be a pointer to a string (this sucks!)
 Expression *union_expr;
 Operator_type union_op;
}

%error-verbose

%token < union_string > T_ID            	 "identifier"
%token < union_int > T_INT_CONSTANT    "int constant"
%token < union_double > T_DOUBLE_CONSTANT "double constant"
%token < union_string > T_STRING_CONSTANT "string constant"

%token T_INT                 "int"
%token T_DOUBLE              "double"
%token T_STRING              "string"
%token T_TRIANGLE            "triangle"
%token T_PIXMAP              "pixmap"
%token T_CIRCLE              "circle"
%token T_RECTANGLE           "rectangle"
%token T_TEXTBOX             "textbox"
%token < union_int > T_FORWARD         "forward" // value is line number
%token T_INITIALIZATION      "initialization"

%token T_TRUE                "true"
%token T_FALSE               "false"

%token T_TOUCHES             "touches"
%token T_NEAR                "near"

%token T_ANIMATION           "animation"

%token T_IF                  "if"
%token T_FOR                 "for"
%token T_ELSE                "else"
%token < union_int > T_PRINT           "print" // value is line number
%token < union_int > T_EXIT            "exit" // value is line number

%token T_LPAREN              "("
%token T_RPAREN              ")"
%token T_LBRACE              "{"
%token T_RBRACE              "}"
%token T_LBRACKET            "["
%token T_RBRACKET            "]"
%token T_SEMIC               ";"
%token T_COMMA               ","
%token T_PERIOD              "."

%token T_ASSIGN              "="
%token T_PLUS_ASSIGN         "+="
%token T_MINUS_ASSIGN        "-="

%token T_ASTERISK            "*"
%token T_DIVIDE              "/"
%token T_MOD                 "%"
%token T_PLUS                "+"
%token T_MINUS               "-"
%token T_SIN                 "sin"
%token T_COS                 "cos"
%token T_TAN                 "tan"
%token T_ASIN                "asin"
%token T_ACOS                "acos"
%token T_ATAN                "atan"
%token T_SQRT                "sqrt"
%token T_FLOOR               "floor"
%token T_ABS                 "abs"
%token T_RANDOM              "random"

%token T_LESS                "<"
%token T_GREATER             ">"
%token T_LESS_EQUAL          "<="
%token T_GREATER_EQUAL       ">="
%token T_EQUAL               "=="
%token T_NOT_EQUAL           "!="

%token T_AND                 "&&"
%token T_OR                  "||"
%token T_NOT                 "!"

%token T_ON                  "on"
%token T_SPACE               "space"
%token T_LEFTARROW           "leftarrow"
%token T_RIGHTARROW          "rightarrow"
%token T_UPARROW             "uparrow"
%token T_DOWNARROW           "downarrow"
%token T_LEFTMOUSE_DOWN      "leftmouse_down"
%token T_MIDDLEMOUSE_DOWN    "middlemouse_down"
%token T_RIGHTMOUSE_DOWN     "rightmouse_down"
%token T_LEFTMOUSE_UP        "leftmouse_up"
%token T_MIDDLEMOUSE_UP      "middlemouse_up"
%token T_RIGHTMOUSE_UP       "rightmouse_up"
%token T_MOUSE_MOVE          "mouse_move"
%token T_MOUSE_DRAG          "mouse_drag"
%token T_F1                  "f1"
%token T_AKEY                "akey"
%token T_SKEY                "skey"
%token T_DKEY                "dkey"
%token T_FKEY                "fkey"
%token T_HKEY                "hkey"
%token T_JKEY                "jkey"
%token T_KKEY                "kkey"
%token T_LKEY                "lkey"
%token T_WKEY                "wkey"

// special token that does not match any production
// used for characters that are not part of the language
%token T_ERROR               "error"

%nonassoc IF_NO_ELSE
%left T_ELSE
%left T_OR
%left T_AND 
%left T_EQUAL T_NOT_EQUAL
%left T_GREATER T_LESS T_GREATER_EQUAL T_LESS_EQUAL
%left T_PLUS T_MINUS
%left T_ASTERISK T_DIVIDE T_MOD
%nonassoc UNARY_OPS

%type<union_int> simple_type
%type<union_expr> optional_initializer;
%type<union_expr> expression;
%type<union_expr> primary_expression;
%type<union_op> math_operator;
%type<union_expr> variable;
%type<union_int> object_type
%type<union_string> animation_parameter

%% // indicates the start of the rules

//---------------------------------------------------------------------
program:
    declaration_list block_list
    ;

//---------------------------------------------------------------------
declaration_list:
    declaration_list declaration
    | empty
    ;

//---------------------------------------------------------------------
declaration:
    variable_declaration T_SEMIC
    | object_declaration T_SEMIC
    | forward_declaration T_SEMIC
    ;

//---------------------------------------------------------------------
variable_declaration:
    simple_type  T_ID  optional_initializer
    {	
	Symbol * s;
	if($1&INT){
		if($3 && (!($3->get_type()&INT))){
			Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->get_type()), *$2, gpl_type_to_string((Gpl_type)$1));
			s=new Symbol(0, *$2);
			Symbol_table::instance()->addSymbol(s);
		}
		else{
			s= new Symbol(($3)?$3->eval_int():0, *$2);
			Symbol_table::instance()->addSymbol(s);
		}
	}
	else if($1&DOUBLE){
		if($3 && (!(($3->get_type()&INT)||($3->get_type()&DOUBLE)))){
			Error::error(Error::INVALID_TYPE_FOR_INITIAL_VALUE, gpl_type_to_string($3->get_type()), *$2, gpl_type_to_string((Gpl_type)$1));
			s=new Symbol(0.0, *$2);
			Symbol_table::instance()->addSymbol(s);
		}
		else{
			s = new Symbol(($3)?$3->eval_double():0.0, *$2);
			Symbol_table::instance()->addSymbol(s);
		}
	}
	else if($1&STRING){
		s=new Symbol(($3)?$3->eval_string():"", *$2);
		Symbol_table::instance()->addSymbol(s);
	}
    }
    | simple_type  T_ID  T_LBRACKET expression T_RBRACKET
    {
	if($4->get_type()&DOUBLE){
		std::stringstream ss; 
		ss << $4->eval_double();
		Error::error(Error::INVALID_ARRAY_SIZE, *$2, ss.str());
	}
	else if($4->get_type()&STRING){
		Error::error(Error::INVALID_ARRAY_SIZE, *$2, $4->eval_string());
	}
	else if($4->eval_int()<1){
		Error::error(Error::INVALID_ARRAY_SIZE, *$2, to_string($4->eval_int()));
	}
	else{
		Symbol*s;
		if($1&INT){
			s=new Symbol(*$2, INT_ARRAY, $4->eval_int());
			Symbol_table::instance()->addSymbol(s);
		}
		if($1&DOUBLE){
			s=new Symbol(*$2, DOUBLE_ARRAY, $4->eval_int());
			Symbol_table::instance()->addSymbol(s);
		}
		if($1&STRING){
			s=new Symbol(*$2, STRING_ARRAY, $4->eval_int());
			Symbol_table::instance()->addSymbol(s);
		}
	}
    }
    ;

//---------------------------------------------------------------------
simple_type:
    T_INT 
    {
	$$ = INT;
    }
    | T_DOUBLE 
    {
	$$= DOUBLE;
    }
    | T_STRING 
    {
	$$=STRING;
    }
    ;

//---------------------------------------------------------------------
optional_initializer:
    T_ASSIGN expression
    {
	$$=$2;
    }
    | empty
    {
	$$=0;
    }
    ;

//---------------------------------------------------------------------
object_declaration:
    object_type T_ID
    {
	switch($1){
		case RECTANGLE:
		cur_object_under_construction = new Rectangle();
		break;
		case TRIANGLE:
		cur_object_under_construction = new Triangle();
		break;
		case CIRCLE:
		cur_object_under_construction = new Circle();
		break;
		case PIXMAP:
		cur_object_under_construction = new Pixmap();
		break;
		case TEXTBOX:
		cur_object_under_construction = new Textbox();
		break;
		default:
		break;
	}
	cur_object_name=*$2;
	Symbol * s=new Symbol(cur_object_under_construction, *$2);
	Symbol_table::instance()->addSymbol(s);
    }
    T_LPAREN parameter_list_or_empty T_RPAREN
    | object_type T_ID T_LBRACKET expression T_RBRACKET
    {
	Symbol* s = new Symbol(*$2, (Gpl_type)($1|ARRAY), $4->eval_int());
	Symbol_table::instance()->addSymbol(s);
    }
    ;

//---------------------------------------------------------------------
object_type:
    T_TRIANGLE
    {
	$$=TRIANGLE;
    }
    | T_PIXMAP
    {
	$$=PIXMAP;
    }
    | T_CIRCLE
    {
	$$=CIRCLE;
    }
    | T_RECTANGLE
    {
	$$=RECTANGLE;
    }
    | T_TEXTBOX
    {
	$$=TEXTBOX;
    }
    ;

//---------------------------------------------------------------------
parameter_list_or_empty :
    parameter_list
    | empty
    ;

//---------------------------------------------------------------------
parameter_list :
    parameter_list T_COMMA parameter
    | parameter
    ;

//---------------------------------------------------------------------
parameter:
    T_ID T_ASSIGN expression
    {
	Status status;
	Gpl_type type;
	status=cur_object_under_construction->get_member_variable_type(*$1, type);
	if(status==MEMBER_NOT_DECLARED){
		Error::error(Error::UNKNOWN_CONSTRUCTOR_PARAMETER, cur_object_under_construction->type(), *$1);
	}
	else{
		if(type&INT){
			if($3->get_type()&INT){
				status = cur_object_under_construction->set_member_variable(*$1, $3->eval_int());
			}
			else{
				Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, cur_object_name, *$1);
			}
		}
		else if(type&DOUBLE){
			if($3->get_type()==INT || $3->get_type()==DOUBLE){
				status = cur_object_under_construction->set_member_variable(*$1, $3->eval_double());
			}
			else{
				Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, cur_object_name, *$1);
			}
		}
		else if(type&STRING){
			if($3->get_type()&INT || $3->get_type()&DOUBLE || $3->get_type()&STRING){
				status = cur_object_under_construction->set_member_variable(*$1, $3->eval_string());
			}
			else{
				Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, cur_object_name, *$1);
			}
		}
		else if(type&ANIMATION_BLOCK){
			if($3->get_type()&ANIMATION_BLOCK){			
				if(!(gpl_type_to_string(($3->eval_animation_block()->get_parameter_symbol()->get_type()))==(cur_object_under_construction->type()))){
					Error::error(Error::TYPE_MISMATCH_BETWEEN_ANIMATION_BLOCK_AND_OBJECT, cur_object_name, "");
				}
				else{
					status = cur_object_under_construction->set_member_variable(*$1, $3->eval_animation_block());
				}
			}
			else{
				Error::error(Error::INCORRECT_CONSTRUCTOR_PARAMETER_TYPE, cur_object_name, *$1);
			}	
		}
	}
    }
    ;

//---------------------------------------------------------------------
forward_declaration:
    T_FORWARD T_ANIMATION T_ID T_LPAREN animation_parameter T_RPAREN
    {
	if($5!=NULL){
		Animation_block* a = new Animation_block();
		Symbol* s = new Symbol(a, *$3);
		Symbol_table::instance()->addSymbol(s);	
		a->initialize(Symbol_table::instance()->lookup(*$5), *$3);
	}
    }
    ;

//---------------------------------------------------------------------
block_list:
    block_list block
    | empty
    ;

//---------------------------------------------------------------------
block:
    initialization_block
    | animation_block
    | on_block
    ;

//---------------------------------------------------------------------
initialization_block:
    T_INITIALIZATION statement_block
    ;

//---------------------------------------------------------------------
animation_block:
    T_ANIMATION T_ID T_LPAREN check_animation_parameter T_RPAREN T_LBRACE { } statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
animation_parameter:
    object_type T_ID
    {
	$$=$2;
	if(Symbol_table::instance()->lookup(*$2)){
		Error::error(Error::ANIMATION_PARAMETER_NAME_NOT_UNIQUE, *$2);
		$$=NULL;
	}
	else{
		switch($1){
			case RECTANGLE:
			cur_object_under_construction = new Rectangle();
			break;
			case TRIANGLE:
			cur_object_under_construction = new Triangle();
			break;
			case CIRCLE:
			cur_object_under_construction = new Circle();
			break;
			case PIXMAP:
			cur_object_under_construction = new Pixmap();
			break;
			case TEXTBOX:
			cur_object_under_construction = new Textbox();
			break;
			default:
			break;
		}
		cur_object_under_construction->never_animate();
		cur_object_under_construction->never_draw();
		Symbol * s=new Symbol(cur_object_under_construction, *$2);
		Symbol_table::instance()->addSymbol(s);
	}
    }
    ;

//---------------------------------------------------------------------
check_animation_parameter:
    T_TRIANGLE T_ID
    | T_PIXMAP T_ID
    | T_CIRCLE T_ID
    | T_RECTANGLE T_ID
    | T_TEXTBOX T_ID
    ;

//---------------------------------------------------------------------
on_block:
    T_ON keystroke statement_block
    ;

//---------------------------------------------------------------------
keystroke:
    T_SPACE
    | T_UPARROW
    | T_DOWNARROW
    | T_LEFTARROW
    | T_RIGHTARROW
    | T_LEFTMOUSE_DOWN
    | T_MIDDLEMOUSE_DOWN
    | T_RIGHTMOUSE_DOWN
    | T_LEFTMOUSE_UP
    | T_MIDDLEMOUSE_UP
    | T_RIGHTMOUSE_UP
    | T_MOUSE_MOVE
    | T_MOUSE_DRAG
    | T_AKEY 
    | T_SKEY 
    | T_DKEY 
    | T_FKEY 
    | T_HKEY 
    | T_JKEY 
    | T_KKEY 
    | T_LKEY 
    | T_WKEY 
    | T_F1
    ;

//---------------------------------------------------------------------
if_block:
    statement_block_creator statement end_of_statement_block
    | statement_block
    ;

//---------------------------------------------------------------------
statement_block:
    T_LBRACE statement_block_creator statement_list T_RBRACE end_of_statement_block
    ;

//---------------------------------------------------------------------
statement_block_creator:
    // this goes to nothing so that you can put an action here in p7
    ;

//---------------------------------------------------------------------
end_of_statement_block:
    // this goes to nothing so that you can put an action here in p7
    ;

//---------------------------------------------------------------------
statement_list:
    statement_list statement
    | empty
    ;

//---------------------------------------------------------------------
statement:
    if_statement
    | for_statement
    | assign_statement T_SEMIC
    | print_statement T_SEMIC
    | exit_statement T_SEMIC
    ;

//---------------------------------------------------------------------
if_statement:
    T_IF T_LPAREN expression T_RPAREN if_block %prec IF_NO_ELSE
    | T_IF T_LPAREN expression T_RPAREN if_block T_ELSE if_block
    ;

//---------------------------------------------------------------------
for_statement:
    T_FOR T_LPAREN statement_block_creator assign_statement end_of_statement_block T_SEMIC expression T_SEMIC statement_block_creator assign_statement end_of_statement_block T_RPAREN statement_block
    ;

//---------------------------------------------------------------------
print_statement:
    T_PRINT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
exit_statement:
    T_EXIT T_LPAREN expression T_RPAREN
    ;

//---------------------------------------------------------------------
assign_statement:
    variable T_ASSIGN expression
    | variable T_PLUS_ASSIGN expression
    | variable T_MINUS_ASSIGN expression
    ;

//---------------------------------------------------------------------
variable:
    T_ID
    {
	if(!Symbol_table::instance()->lookup(*$1)){
		Error::error(Error::UNDECLARED_VARIABLE, *$1);
		$$=new Expression(0);
	}
	else{
		Variable* v = new Variable(Symbol_table::instance()->lookup(*$1));
		Expression* e = new Expression(v);
		$$=e;
	}
    }
    | T_ID T_LBRACKET expression T_RBRACKET
    {
	if(!((Symbol_table::instance()->lookup(*$1)->get_type())&ARRAY)){
		Error::error(Error::VARIABLE_NOT_AN_ARRAY, *$1);
		$$=new Expression(0);
	}
	else if($3->get_type()&DOUBLE){
		Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A double expression");
		$$= new Expression(0);
	}
	else if($3->get_type()&STRING){
		Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, *$1, "A string expression");
		$$= new Expression(0);
	}
	else{
		if(Symbol_table::instance()->lookup(*$1)->get_size()<$3->eval_int()){
			Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, *$1, to_string($3->eval_int())); 
			Variable*v= new Variable(Symbol_table::instance()->lookup(*$1), 0);
			Expression* e = new Expression(v);
			$$=e;
		}
		else{
			Variable* v = new Variable(Symbol_table::instance()->lookup(*$1), $3);
			Expression* e = new Expression(v);
			$$=e;
		}
	}
    }
    | T_ID T_PERIOD T_ID
    {
	Gpl_type type;
	if(!Symbol_table::instance()->lookup(*$1)){
		Error::error(Error::UNDECLARED_VARIABLE, *$1);
		$$=new Expression(0);
	}
	else if(!(Symbol_table::instance()->lookup(*$1)->get_type()&GAME_OBJECT)){
		Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
		$$=new Expression(0);
	}
	else if(Symbol_table::instance()->lookup(*$1)->get_game_object_value()->get_member_variable_type(*$3, type)==MEMBER_NOT_DECLARED){
		Error::error(Error::UNDECLARED_MEMBER, *$1, *$3);
		$$=new Expression(0);
	}
	else{
		Symbol* obj = Symbol_table::instance()->lookup(*$1);
		Variable* v = new Variable(obj, *$3);
		$$ = new Expression(v);
	}
    }
    | T_ID T_LBRACKET expression T_RBRACKET T_PERIOD T_ID
    {
	if(!Symbol_table::instance()->lookup(*$1)){
		Error::error(Error::UNDECLARED_VARIABLE, *$1);
		$$=new Expression(0);
	}
	else if(!(Symbol_table::instance()->lookup(*$1)->get_type()&GAME_OBJECT)){
		Error::error(Error::LHS_OF_PERIOD_MUST_BE_OBJECT, *$1);
		$$=new Expression(0);
	}
	else{
		Symbol* obj = Symbol_table::instance()->lookup(*$1);
		Variable * v = new Variable(obj, *$6, $3);
		$$= new Expression(v);
	}
    }
    ;

//---------------------------------------------------------------------
expression:
    primary_expression
    {
	$$=$1;
    }
    | expression T_OR expression
    {
	if(($1->get_type()&STRING)||($3->get_type()&STRING)){
		if($1->get_type()&STRING){
			Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "||");
			$$=new Expression(0);
		}
		if($3->get_type()&STRING){
			Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "||");
			$$=new Expression(0);
		}
	}
	else{
		$$=new Expression($1, OR, $3);
	}
    }
    | expression T_AND expression
    {
        if($1->get_type()&STRING){
		Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "&&");
		$$=new Expression(0);
		if($3->get_type()&STRING){
			Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
			$$=new Expression(0);
		}
	}
	else if($3->get_type()&STRING){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "&&");
		$$=new Expression(0);
	}
	else{
		$$=new Expression($1, AND, $3);
	}
    }
    | expression T_LESS_EQUAL expression
    {
        $$=new Expression($1, LESS_THAN_EQUAL, $3);
    }
    | expression T_GREATER_EQUAL  expression
    {
        $$=new Expression($1, GREATER_THAN_EQUAL, $3);
    }
    | expression T_LESS expression 
    {
        $$=new Expression($1, LESS_THAN, $3);
    }
    | expression T_GREATER  expression
    {
        $$=new Expression($1, GREATER_THAN, $3);
    }
    | expression T_EQUAL expression
    {
        $$=new Expression($1, EQUAL, $3);
    }
    | expression T_NOT_EQUAL expression
    {
        $$=new Expression($1, NOT_EQUAL, $3);
    }
    | expression T_PLUS expression 
    {
        $$=new Expression($1, PLUS, $3);
    }
    | expression T_MINUS expression
    {
	if($1->get_type()&STRING){
		Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "-");
		$$=new Expression(0);
	}
	if($3->get_type()&STRING){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-");
		$$=new Expression(0);
	}
	else{
		$$=new Expression($1, MINUS, $3);
	}
    }
    | expression T_ASTERISK expression
    {
	if($1->get_type()&STRING){
		Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "*");
		$$=new Expression(0);
	}
	if($3->get_type()&STRING){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "*");
		$$=new Expression(0);
	}
	else{
		$$=new Expression($1, MULTIPLY, $3);
	}
    }
    | expression T_DIVIDE expression
    {
	 if($1->get_type()&STRING){
		Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "/");
		$$=new Expression(0);
	}
	if($3->get_type()&STRING){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "/");
		$$=new Expression(0);
	}
	else{
		if((($3->get_type()&INT)&&(!($3->eval_int())))||(($3->get_type()&DOUBLE)&&(!($3->eval_double())))){
			Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
			$$=new Expression(0);
		}
		else{
			$$=new Expression($1, DIVIDE, $3);
		}
	}
    }
    | expression T_MOD expression
    {
	 if(($1->get_type()&STRING)||($1->get_type()&DOUBLE)){
		Error::error(Error::INVALID_LEFT_OPERAND_TYPE, "%");
		$$=new Expression(0);
	}
	if(($3->get_type()&STRING)||($3->get_type()&DOUBLE)){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "%");
		$$=new Expression(0);
	}
	else{
		if(!($3->eval_int())){
			Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
			$$=new Expression(0);
		}
		else{
			$$=new Expression($1, MOD, $3);
		}
	}
    }
    | T_MINUS  expression %prec UNARY_OPS
    {
	if($2->get_type()&STRING){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "-");
		$$=new Expression(0);
	}
	else{
		$$=new Expression($2, UNARY_MINUS);
	}
    }
    | T_NOT  expression %prec UNARY_OPS
    {
	if($2->get_type()&STRING){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, "!");
		$$=new Expression(0);
	}
	else{
		$$=new Expression($2, NOT);
	}
    }
    | math_operator T_LPAREN expression T_RPAREN
    {
	if($3->get_type()&STRING){
		Error::error(Error::INVALID_RIGHT_OPERAND_TYPE, operator_to_string($1));
		$$=new Expression(0);
	}
	else{
		$$=new Expression($3, $1);
	}
    }
    | variable geometric_operator variable
    {
	$$=new Expression(0);
    }
    ;

//---------------------------------------------------------------------
primary_expression:
    T_LPAREN  expression T_RPAREN
    {
	$$=$2;
    }
    | variable
    {
        $$=$1;
    }
    | T_INT_CONSTANT
    {
        $$=new Expression($1);
    }
    | T_TRUE
    {
	$$=new Expression(1);
    }
    | T_FALSE
    {
	$$=new Expression(0);
    }
    | T_DOUBLE_CONSTANT
    {
	$$=new Expression($1);
    }
    | T_STRING_CONSTANT
    {
	$$=new Expression(*$1);
    }
    ;

//---------------------------------------------------------------------
geometric_operator:
    T_TOUCHES
    | T_NEAR
    ;

//---------------------------------------------------------------------
math_operator:
    T_SIN
    {
	$$=SIN;
    }
    | T_COS
    {
	$$=COS;
    }
    | T_TAN
    {
	$$=TAN;
    }
    | T_ASIN
    {
	$$=ASIN;
    }
    | T_ACOS
    {
        $$=ACOS;
    }
    | T_ATAN
    {
        $$=ATAN;
    }
    | T_SQRT
    {
        $$=SQRT;
    }
    | T_ABS
    {
	$$=ABS;
    }
    | T_FLOOR
    {
	$$=FLOOR;
    }
    | T_RANDOM
    {
	$$=RANDOM;
    }
    ;

//---------------------------------------------------------------------
empty:
    // empty goes to nothing so that you can use empty in productions
    // when you want a production to go to nothing
    ;
