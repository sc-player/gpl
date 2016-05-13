/*
  Gpl_type are the types in gpl

  string gpl_type_to_string(Gpl_type gpl_type) returns a C++ string for
  the given type

  The enumerated type Gpl_type has an associated operator<< so it is easy
  to print.
*/

#ifndef GPL_TYPE_H
#define GPL_TYPE_H

#include <string>

// assign powers of 2 so that bitwise operations can be used
enum Gpl_type {NO_TYPE = 0,
               INT = 1,
               DOUBLE = 2,
               STRING = 4,
               ANIMATION_BLOCK = 8,
               GAME_OBJECT = 16,
               CIRCLE = 32 + GAME_OBJECT,
               RECTANGLE = 64 + GAME_OBJECT,
               TRIANGLE = 128 + GAME_OBJECT,
               TEXTBOX = 256 + GAME_OBJECT,
               PIXMAP = 512 + GAME_OBJECT,
               ARRAY = 1024,
               INT_ARRAY = INT + ARRAY,
               DOUBLE_ARRAY = DOUBLE + ARRAY,
               STRING_ARRAY = STRING + ARRAY,
               GAME_OBJECT_ARRAY = GAME_OBJECT + ARRAY,
               CIRCLE_ARRAY = CIRCLE + ARRAY,
               RECTANGLE_ARRAY = RECTANGLE + ARRAY,
               TRIANGLE_ARRAY = TRIANGLE + ARRAY,
               TEXTBOX_ARRAY = TEXTBOX + ARRAY,
               PIXMAP_ARRAY =  PIXMAP + ARRAY
              };

std::string gpl_type_to_string(Gpl_type gpl_type);

enum Status {OK,
             MEMBER_NOT_OF_GIVEN_TYPE,
             MEMBER_NOT_DECLARED
             };

std::string status_to_string(Status status);

enum Operator_type {PLUS, MINUS, MULTIPLY, DIVIDE, MOD,
                    UNARY_MINUS, NOT,
                    AND, OR,
                    EQUAL, NOT_EQUAL,
                    LESS_THAN, LESS_THAN_EQUAL,
                    GREATER_THAN, GREATER_THAN_EQUAL,
                    NEAR, TOUCHES,
                    SIN, COS, TAN,
                    ASIN, ACOS, ATAN,
                    SQRT, FLOOR, ABS, RANDOM
                   };

std::string operator_to_string(Operator_type op);

#endif // #ifndef GPL_TYPE_H
