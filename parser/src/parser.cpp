

/*BUG*/ // this file will quickly grow too big and must be broken up
#include <stdio.h>
#include <stdint.h>

#include "../../lexical/src/lexical.h"  /*BUG*/ //Need to call this through the right directory!

#define EXTERN


/* #define ispunc(lexeme, punct) { (lexeme.type == PUNCT) && \
//                                 (lexeme.value == punct); \
                               }
*/

#define ispunc( lex, set ) ((lex.type == LEX_PUNC) && ((1 << lex.value) & (set))
#define makeset2( a, b ) ( (1 << (a)) | (1 << (b)) )

// void parse_program() {
//   // <kestrel program> ::= <block> <end of file>
//   parse_block();
//   lex_force( ENDFILE );
// }

// void parse_block() {
//   while ( (lex_this.type == IDENT)
//         ||      (iskeyset( lex_this, STATEMENT_KEYWORDS ))
//         ) { // there are more block elements
//     if ( (lex_this.type == IDENT)
//     &&   (ispunc( lex_next, PT_COLON ))) {
//       parse_declaration();
//     } else {
//       parse_statement();
//     }
//     if (lex_ispunc( lex_this, PT_SEMCOL )) lex_advance();
//   }
// }

/**************************************************
*
*     TYPE STUFF
*     http://homepage.cs.uiowa.edu/~jones/compiler/kestrel/definition.shtml#Types
*
* **************************************************/

void parse_type() {
  /* <type> ::= <reference>
                |  <enumeration>
                |  <subrange>
                |  <pointer>
                |  <array>
                |  <record>
  */
 
 /* References reduce down to identifiers */
 /*BUG*/ /* Not sure if I'm looking for the right start for reference.
          * Might need to look at lex_next to decide.
          */
         
  if (lex_this.type == IDENT) {
    parse_reference();
  }

  else if (lex_this.type == KEYWORD) {
    /* Enums start with the keyword "enum" */
    if (lex_this.value == KW_ENUM) {
      parse_enumeration();
    }
    /* Arrays start with the array keyword */
    else if (lex_this.value == KW_ARRAY) {
      parse_array();
    }
    /* Records start with record keyword */
    else if (lex_this.value == KW_RECORD) {
      parse_record();
    }
  }

  else if (lex_this.type == PUNCT) {
    /* Pointer's start with an @ */
    if (lex_this.value == PT_AT) {
      parse_pointer();
    }
    else {
      /* BUG */ /* Does anything else need to happen? */ 
    }

  }
  else {
    /*BUG*/ /* Not sure if this should default to subrange...*/
    parse_subrange();
  }

}

void parse_enumeration() {
  /* <enumeration> ::= "enum" "(" <identifier> { [","] <identifier>} ")"
                         |  "enum" "[" <identifier> { [","] <identifier>} "]"
                         |  "enum" "{" <identifier> { [","] <identifier>} "}"
  */
 
 /* get past "enum" */
 lex_advance();
 if (lex_this.type == PUNCT) {
  if((lex_this.value == PT_LPAREN) || (lex_this.value == PT_LBRAKT) || (lex_this.value == PT_LBRACE)) {
    /*BUG*/ /* Consume Identifiers */

  }
 }


}

void parse_subrange() {
  /* <subrange> ::= <expression> ".." <expression> */


}

void parse_pointer() {
  /* <pointer> ::= "@" <type> */

}

void parse_array() {
  /* <array> ::= "array" <type> "of" <type> */

}

void parse_record() {
  /* <record> ::= "record" <block> "end" */

}

/**********************************
*
*   Declaration Stuff
*   http://homepage.cs.uiowa.edu/~jones/compiler/kestrel/definition.shtml#Declarations
*
* *********************************/

void parse_declaration() {
  /* <identifier> ":" [ "private" ] <entity> */

}

void parse_entity() {
  /* <entity> ::= <constant constructor>
                  |  <type constructor>
                  |  <exception constructor>
                  |  <variable constructor>
                  |  <procedure constructor>
                  |  <function constructor>
  */
 
}

void parse_const_constr() {
  /* <constant constructor> ::= "const" <expression> */
}

void parse_type_constr() {
  /* <type constructor> ::= "type" <type> */
}

void parse_exception_constr() {
  /* <exception constructor> ::= "exception" */
}

void parse_variable_constr() {
  /* <variable constructor> ::= "var" <type> */
}

void parse_procedure_constr() {
  /* <procedure constructor> ::= "procedure"
                                    [ <formal parameters> ]
                                    <body>
  */
}

void parse_function_constructor() {
  /*  <function constructor> ::=  "function" <type>
                                    [ <formal parameters> ]
                                    <body>
  */
 
}

void parse_formal_parameters() {
  /* <formal parameters> ::= "(" <parameter> { [","] <parameter>} ")"
                             |  "[" <parameter> { [","] <parameter>} "]"
                             |  "{" <parameter> { [","] <parameter>} "}"
  */
 
}

void parse_parameter() {
  /* <parameter> ::= <identifier> ":" <parameter constructor> */


}

void parse_function_body() {
  /* <body> ::= "external"
                |  <block> "end"
  */
}


void parse_parameter_constructor() {
  /* <parameter constructor> ::= "var" <type>
                                 |  "const" <type>
  */
}


/********************************
*
* Statements
* http://homepage.cs.uiowa.edu/~jones/compiler/kestrel/definition.shtml#Statements
* ********************************/

/* NOTE: Need start sets for last 3, since they all use reference further down the recursion */

void parse_statement() {
  /*
  <statement>::=  <if>  | <case>
        | <loop>
        | <handler>
        | <raise>
        | <procedure call>
        | <assignemnt>
  This is seen in Lect.17
  */
  if (lex_this.type == IDENT) { // it is a procedure call or assignment
  } 
  else { // other types of statements
    if (lex_is( lex_this, KEYWORD, KEY_IF )) 
    { /* If keyword is 'if'  */
          parse_if();
    } 
    else if (lex_is( lex_this, KEYWORD, KEY_SEL )) {
      parse_case();
    } 
    else if ( lex_is( lex_this, KEYWORD, key_FOR   )
              lex_is( lex_this, KEYWORD, key_WHILE )
              lex_is( lex_this, KEYWORD, key_DO    ) )
    {
      parse_loop(); /*BUG*/ //parse_loop() IS NOT FINISHED YET!
    }
    else if
    {
      /*BUG*/ //missing alternatives and errors
              //KEYWORDS MISSING ARE TRY and RAISE
              //Error statements missing ARE A LOT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
  }
}

void parse_if() {
  /* <if> ::= "if" <expression> [ "then" ]
                     <block>
               [ "else"
                     <block> ]
                 "end"
  */
 
}

void parse_case() {
  /* <case> ::= "select" <expression> [ "in" ]
               { "case" <case label> { [ "," ] <case label> } ":"
                     <block> }
               [ "else"
                     <block> ]
                 "end"
  */
 
}

void parse_case_label() {
  /* <case label> ::= <expression> [ ".." <expression> ] */

}

void parse_loop(){
  /* <loop> ::= <while loop>
                 |  <until loop>
                 |  <for loop>
  */

  if      (lex_is(lex_this, KEYWORD, key_WHILE))    parse_while();
  else if (lex_is(lex_this, KEYWORD, key_DO))  parse_do();
  else if (lex_is(lex_this, KEYWORD, key_FOR)) parse_for();
  /*BUG*/ //missing all of the above!!!!

}

void parse_while() {
  /*  <while loop> ::= "while" <expression> [ "do" ]
                             <block>
                         "end"
  */
}

void parse_do() {
  /* <until loop> ::= "do"
                             <block>
                         "until" <expression>
  */
 
}

void parse_for() {
  /* <for loop> ::= "for" <identifier> "in" <type> [ "do" ]
                           <block>
                       "end"
  */
 
}

void parse_handler() {
  /* <handler> ::= "try"
                          <block>
                    { "handle" <reference> { [ "," ] <reference> } ":"
                          <block> }
                    [ "else"
                          <block> ]
                      "end"
  */
 
}

void parse_raise() {
  /* <raise> ::= "raise" <reference> */

}

void parse_procedure_call() {
  /* <procedure call> ::= <reference> */

}

void parse_assignment() {
  /* <assignment> ::= <reference> "=" <expression> */
}

/*********************************************
*
*   Expressions
*   http://homepage.cs.uiowa.edu/~jones/compiler/kestrel/definition.shtml#Expressions
*   
**********************************************/


void parse_expression() {
  /* <expression> ::= <comparand> [ <comparing operator> <comparand> ] */

}

void parse_comparand() {
  /* <comparand> ::= <term> { <adding operator> <term> } */

}

void parse_term() {
  /* <term> ::= <factor> { <multiplying operator> <factor> } */

}

/* BUG */ /* Might not even need this, probably just going to first figure out which 
           * one it actually is and do logic from there
           * Ex: if (lexeme == "=") {Do stuff}
           *     else if (lexeme == "<>"") { Do different stuff }
           * which should give you back a boolean. Not 100% sure though.
           */

void parse_comparing_operator() {
  /* <comparing operator> ::= "="
                              |  "<>"
                              |  ">"
                              |  ">="
                              |  "<"
                              |  "<="
  */
}

/* BUG */ /* Same as above, probably just going to evaluate which one it is in term */

void parse_adding_operator() {
  /* <adding operator> ::= "+"
                           |  "-"
                           |  "|"
  */
 
}

/* BUG */ /* Once again, same as above 2 */

void parse_multiplying_operator() {
  /* <multiplying operator> ::= "*"  -- multiplication
                                |  "/"  -- division
                                |  "&" -- logical and
  */
 
}

void parse_factor() {
 /* <factor> ::= [ "-" | "~" ] <value> */

}

void parse_value() {
  /* <value> ::= <number>
                 |  <string constant>
                 |  "null"
                 |  <reference>
                 |  <subexpression>
  */
 
}

void parse_subexpression() {
  /* <subexpression> ::= "(" <expression> ")"
                         |  "[" <expression> "]"
                         |  "{" <expression> "}"
  */
 
}

void parse_string_const() {
  /* <string constant> ::= <string> { <string> | <expression> } */

}

void parse_reference() {
  /* <reference> ::= <identifier>
                     |  <reference> "@"
                     |  <reference> "." <identifier>
                     |  <reference> <parameter or index>
  */
 
}

/* BUG*/ /* Potentially similar situation as the adding operators since all that differs is
          * the grouping symbols ("()", "[]", "{}") */

void parse_parameter_or_index() {
  /* <parameter or index> ::= "(" <expression> { "," <expression> } ")"
                              |  "[" <expression> { "," <expression> } "]"
                              |  "{" <expression> { "," <expression> } "}"
  */
}