/* lexical.h
 *    Kestrel lexical analyzer interface spec
 *       by D.W.Jones
 */

#ifndef EXTERN
	#define EXTERN extern
#endif

#include "errors.h"
#include <stdio.h>
#include <stdint.h>
#include "config.h"
#include "symboltable.h"


typedef enum lex_types { 
	IDENT, KEYWORD, NUMBER, STRING, PUNCT, ENDFILE, UNKNOWN 
} lex_types;

typedef struct lexeme {
	lex_types type;
	uint32_t value;
	int line;
	int column;
} lexeme;

extern lexeme lex_this; /* the current lexeme */
extern lexeme lex_next; /* the next lexeme    */
extern int cur_line;
extern int cur_column;

/* if the lex.type is PUNCT, lex.value will be one of these */
enum punct_type {
    PT_EQUALS /* = */,   PT_COLON  /* : */, 
    PT_LPAREN /* ( */,   PT_RPAREN /* ) */, 
    PT_LBRAKT /* [ */,   PT_RBRAKT /* ] */, 
    PT_LBRACE /* { */,   PT_RBRACE /* } */, 
    PT_COMMA  /* , */,   PT_ATSIGN /* @ */, 
    PT_ELIPS  /* .. */,  PT_NOTEQL /* <> */, 
    PT_GT     /* > */,   PT_GE     /* >= */, 
    PT_LT     /* < */,   PT_LE     /* <= */, 
    PT_PLUS   /* + */,   PT_MINUS /* - */, 
    PT_TIMES  /* * */,   PT_DIV    /* / */, 
    PT_AND    /* & */,   PT_OR     /* | */, 
    PT_DOT    /* . */,   PT_SEMIC  /* ; */,
    PT_TILDE  /* ~ */ 
};

/* types of characters */
typedef enum char_type {
  OTH=0, /* other */
  WIT=1, /* whitespace */
  LET=2, /* letter */
  DIG=4, /* digit */
  PUN=8  /* punctuation */
} char_type;


void lex_open( char * f ); /*changed from `const char` */
void lex_advance();
void lex_put( lexeme * lex, FILE * f );

#define ISCLASS(ch,class) (char_class[ch]&(class))

/* flopLex is to switch up lex_this and lex_next in lexical.c  */
#define flopLex(lex1, lex2) { lex1 = lex2;  } 
/* it's not necessary to assign each attribute. This does the same thing. */

#define isLex(lex, type, value){ ((lex).type==(t));         \
                                 &&                         \
                                 ((lex).value == (v)) }     

#define createLex(lex, t, v, l, c) { lex.type  = t;         \
                                    lex.value  = v;         \
                                    lex.line   = l;         \
                                    lex.column = v; }


#define lex_in_set( lex, set ) (IN_SET32( (lex).value, set ))


#undef EXTERN
