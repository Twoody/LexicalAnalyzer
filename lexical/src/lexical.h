/*
 *Restart of lexical.
 */

#ifndef LEXICAL_H_
#define LEXICAL_H_

#ifndef EXTERN
  #define EXTERN extern
#endif

typedef enum lex_types {
        IDENT, KEYWORD, NUMBER, STRING, PUNCT, ENDFILE, UNKNOWN
} lex_types;


typedef struct lexeme {
	lex_types type;
	uint32_t value;
	int line;
	int column;
} lexeme;

EXTERN lexeme lex_this; /* the current lexeme */
EXTERN lexeme lex_next; /* the next lexeme    */
EXTERN int cur_line;
EXTERN int cur_column;


// types of characters
typedef enum char_type { 
  OTH=0, /* other */
  WIT=1, /* whitespace */
  LET=2, /* letter */
  DIG=4, /* digit */
  PUN=8  /* punctuation */
} char_type;


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
    PT_TILDE  /* ~ */,
    NOPE      /* False Alarm, yo. */
};


// open lexical analyzer to read from a file named f, or stdin if f is null
void lex_open( char * f );

// advance lex_this and lex_next one lexeme
void lex_advance();

// output lexeme to f with no decorations
void lex_put( lexeme * lex, FILE * f );

#define ISCLASS(ch,class) (char_class[ch]&(class))

#define lex_in_set( lex, set ) (IN_SET32( (lex).value, set ))

#define createLex(lex, t, v, l, c) { lex.type  = t;         \
                                    lex.value  = v;         \
                                    lex.line   = l;         \
                                    lex.column = v; }

#define flopLex(lex1, lex2) { lex1.type  = lex2.type;   \
                              lex1.value = lex2.value;  \
                              lex1.line  = lex2.line;   \
                              lex1.column   = lex2.column; }

#define isLex(lex, type, value){ ((lex).type==(t));         \
                                 &&                         \
                                 ((lex).value == (v)) }     


punct_type __punct_type__();

#undef EXTERN

#endif /* LEXICAL_H */
