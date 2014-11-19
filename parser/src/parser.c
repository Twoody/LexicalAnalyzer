

/*BUG*/ // this file will quickly grow too big and must be broken up
#include <stdio.h>
#include <stdint.h>

#include "lextools.h" /*BUG*/ //Need to call this through the right directory!
#include "lexical.h"  /*BUG*/ //Need to call this through the right directory!

#define EXTERN
#include "parser.h"

void parse_case() {
  /* <case> ::= "select" <expression> [ "in" ]
               { "case" <case label> { [ "," ] <case label> } ":"
                     <block> }
               [ "else"
                     <block> ]
                 "end"
  */
}

void parse_case_labe() {
  /* <case label> ::= <expression> [ ".." <expression> ] */
  
}

void parse_declaration() {
  /* <identifier> ":" [ "private" ] <entity> */

}

void parse_if() {
}

void parse_loop(){
  if      (lex_is(lex_this, KEYWORD, key_WHILE))    parse_while();
  else if (lex_is(lex_this, KEYWORD, key_DO))  parse_do();
  else if (lex_is(lex_this, KEYWORD, key_FOR)) parse_for();
  /*BUG*/ //missing all of the above!!!!

}

void parse_statement() {
  /*
	<statement>::= 	<if>	|	<case>
				|	<loop>
				|	<handler>
				|	<raise>
				|	<procedure call>
				|	<assignemnt>
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

void parse_block() {
  // <block> ::= { <block element> [ ";" ] }
  // <block element> ::= <declaration> | <statement>
  while( true /*BUG*/ /* lex_this is member of start set for block elem */ ) {
    if (lex_is( lex_next, PUNCT, PT_COLON )) {
      parse_declaration();
    } else {
      parse_statement();
    }
    if (lex_is( lex_this, PUNCT, PT_SEMIC )) {
      lex_advance();
    }
  }
}

void parse_program() {
  // <kestrel program> ::= <block> <end of file>
  parse_block();
  lex_force( ENDFILE );
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

void parse_type() {
  /* <type> ::= <reference>
                |  <enumeration>
                |  <subrange>
                |  <pointer>
                |  <array>
                |  <record>
  */
}

void parse_enumeration() {
  /*<enumeration> ::= "enum" "(" <identifier> { [","] <identifier>} ")"
                         |  "enum" "[" <identifier> { [","] <identifier>} "]"
                         |  "enum" "{" <identifier> { [","] <identifier>} "}"
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

void parse_function_constr() {
  /* <function constructor> ::=  "function" <type>
                                    [ <formal parameters> ]
                                    <body>
  */
 

}

void parse_body() {
  /* <body> ::= "external"
                |  <block> "end"
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

void parse_constructor() {
  /* <parameter constructor> ::= "var" <type>
                                 |  "const" <type>
  */
}

void parse_type() {
  /* <type> ::= <reference>
                |  <enumeration>
                |  <subrange>
                |  <pointer>
                |  <array>
                |  <record>
  */
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

