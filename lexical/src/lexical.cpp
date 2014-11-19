/*
 *Restart of Lexical.cpp
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "config.h"
#include "stringpool.h"
#include "symboltable.h"
#include "error.h"

#define EXTERN
#include "lexical.h"


FILE *infile;     /* Lets declare that we use a file!!!            */
int ch;           /* The current character (type char) or EOF      */
int nextCh;       /* The character following the current character */
int value;
#define nextchar() { 		\
   ch = nextCh;		      \
   nextCh = getc(infile);	\
   cur_column +=1;		   \
}

static const char_type char_class[256] = {

  /* NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI */
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,WIT,WIT,WIT,WIT,WIT,OTH,OTH,
  /* DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US */
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
  /*      !   "   #   $   %   &   '   (   )   *   +   ,   -   .   / */
     WIT,OTH,OTH,OTH,OTH,OTH,PUN,OTH,PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
  /*  0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ? */
     DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,PUN,PUN,PUN,PUN,PUN,OTH,
  /*  @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O */
     PUN,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
  /*  P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _ */
     LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,OTH,PUN,OTH,OTH,
  /*  `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o */
     OTH,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
  /*  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL*/
     LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,PUN,PUN,PUN,OTH,
  /* beyond ASCII                                                   */
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH
};

bool isString(){
  if (ch=='"' || ch=='\'') {return true;}
  else                     {return false;}
}

bool isNumber(){
  if ( ch>='0' && ch<='9'  ) {return true;}
  else                       {return false;}
}

bool isAlpha(){
  if( (ch>='a' && ch<='z')  || (ch>='A' && ch<='Z')   ) {return true;}
  else                                                  {return false;}
}

bool isIdent(){
  if(isAlpha() || ch == '_') {return true;}
  else                       {return false;}
}

bool isIdent_v2(){
  if (isIdent() || isNumber()){return true;}
  else                        {return false;}
}

bool isNextNumber(){
  if ( nextCh>='0' && nextCh<='9'  ) {return true;}
  else                               {return false;}
}

bool isNextAlpha(){
  if      (nextCh>='a' && nextCh<='z') {return true;}
  else if (nextCh>='A' && nextCh<='Z') {return true;}
  else                                 {return false;}
}

bool isNextIdent(){
  if     ( isNextNumber())   {return true;}
  else if( isNextAlpha())    {return true;}
  else if( nextCh=='_')      {return true;}
  else                       {return false;}
}

bool isWhite(){
  if( ch=='\n' || ch=='\r' || ch=='\t' || ch==' '){
    return true;
  }
  return false;
}

bool isNextWhite(){
  if( nextCh=='\n' || nextCh=='\r' || nextCh=='\t' || nextCh==' '){
    return true;
  }
  return false;
}

bool  isComment(){
  if (ch == '-' && nextCh =='-') {return true;}
  else                           {return false;}
}

bool isWeird(){
 return false;
}

void __comment__() {
  while ((ch != '\n') && (ch != EOF)) {nextchar();}
  cur_line  += 1;
  cur_column = 0;
}

void __whitespace__() {
  while (isWhite() || isComment()) {
    if (ch == '\n') {
      cur_line  += 1;
      cur_column = 0;
    }
    else if (isComment())
      __comment__();
    nextchar();
  }
}

/*************************************************************************
 * LINK: http://homepage.cs.uiowa.edu/~jones/compiler/spring13/notes/06.shtml
 * **************************************************************************/
punct_type __punct_type__()
{
  if (ch=='=')      {return PT_EQUALS; }                      /* = */
  else if (ch==':') {return PT_COLON;  }                      /* : */
  else if (ch=='(') {return PT_LPAREN; }                      /* ( */
  else if (ch==')') {return PT_RPAREN; }                      /* ) */
  else if (ch=='[') {return PT_LBRAKT; }                      /* [ */
  else if (ch==']') {return PT_RBRAKT; }                      /* ] */
  else if (ch=='{') {return PT_LBRACE; }                      /* { */
  else if (ch=='}') {return PT_RBRACE; }                      /* } */
  else if (ch==',') {return PT_COMMA;  }                      /* , */
  else if (ch=='@') {return PT_ATSIGN; }                      /* @ */
  else if (ch=='+') {return PT_PLUS;   }                      /* + */
  else if (ch=='-') {return PT_MINUS;  }                      /* - */
  else if (ch=='*') {return PT_TIMES;  }                      /* * */
  else if (ch=='/') {return PT_DIV;    }                      /* / */
  else if (ch=='&') {return PT_AND;    }                      /* & */
  else if (ch=='|') {return PT_OR;     }                      /* | */
  else if (ch==';') {return PT_SEMIC;  }                      /* ; */
  else if (ch=='~') {return PT_TILDE;  }                      /* ~ */
  else if (ch=='<'){
    if      (nextCh == '>') { nextchar(); return PT_NOTEQL;}              /* <> */
    else if (nextCh == '=') { nextchar(); return PT_LE;    }              /* <= */
    else                                 {return PT_LT;    }              /* <  */
  }
  else if(ch=='>'){ 
    if (nextCh == '=') { nextchar(); return PT_GE; }                      /* >= */
    else                           { return PT_GT; }                      /* >  */
  }
  else if(ch=='.'){
    if (nextCh == '.') { nextchar();  return PT_ELIPS; }                  /* .. */
    else                            { return PT_DOT;   }                  /* .  */
  }
  else {return NOPE;}
}/* End of get_punct_type()  */

void __punctuation__()
{/*Uses punct_type above; returns -1 if not in table*/
  lex_next.value = __punct_type__(); 
  if (lex_next.value == NOPE)
  {
    printf("WE REALLY SHOULDN'T BE HERE!\n");
    error_fatal(ER_ILLGLPUNCT, "LEXICAL", cur_line, cur_column);
  }
    createLex(lex_next, PUNCT, lex_next.value, cur_line, cur_column);
}//End Punctuation

void __string__()
{
  int openingQuote = ch;
  symbol_start();
  nextchar();
  while (ch != openingQuote) {
    symbol_append(ch);
    if      (ch == '\n')
      error_fatal(ER_LEXSTRNL, "Lexical", cur_line, cur_column);
    else if (ch == EOF)
      error_fatal(ER_LEXSTREOF, "Lexical", cur_line, cur_column);
    else if (ch=='\\'){
      if (nextCh == '\''){nextchar();symbol_append(ch);nextchar();}
      else if (nextCh == '"') {nextchar();symbol_append(ch);nextchar();}
      else if (nextCh == '\n'){error_fatal(ER_LEXSTRNL, "Lexical", cur_line, cur_column);}
      else {nextchar();}
    }
    else{nextchar();}
  }
 string_done();
 symbol_handle h = symbol_lookup();
 createLex(lex_next, STRING, h, cur_line, cur_column);
 }//End String

void __ident__()
{
  symbol_start();                 	        /* reset _symbol_hash to 0 */
  symbol_append(ch);                    	/* append first element    */
  while (isNextIdent())
  {
    nextchar();
    if (isIdent_v2()) {symbol_append(ch);}      /* eat all of the letters and numbers */
  }


  symbol_handle h = symbol_lookup();
  string_done();
  createLex(lex_next, IDENT, h, cur_line, cur_column);
}//End __ident__()

int __extended_num__(int radix)
{/* function to convert extended number to decimal value
    used in number accumulation of lex_advance()         */
  int ext_val = 0;
  int digit ;
  while (isNextNumber() || isNextAlpha()) 	
  {
/* If alpha, then convert to digit. 
 * There is a BUG with u. 
 * The math was acquired from Python.
 * Some letters are omitted due to their appearance
 */									
    if(isNextAlpha())
    {
      if     ( nextCh == 'l' || nextCh == 'L' ) { digit = 1; }
      else if( nextCh == 'i' || nextCh == 'I' ) { digit = 1; }
      else if( nextCh == 'o' || nextCh == 'O' ) { digit = 0; }
      else if( nextCh == 'u' || nextCh == 'U' ) { digit = 32;} /*BUG*/ //TALK TO JONES ABOUT u && U
      else if( nextCh >= 'a' && nextCh <= 'h' ) {digit = nextCh-'0'-37;}
      else if( nextCh == 'j' || nextCh == 'k' ) {digit = nextCh-'0'-38;}	
      else if( nextCh >= 'm' || nextCh <= 'n' ) {digit = nextCh-'0'-39;}
      else if( nextCh >= 'p' && nextCh <= 't' ) {digit = nextCh-'0'-40;}
      else if( nextCh >= 'v' && nextCh <= 'z' ) {digit = nextCh-'0'-41;}
      else if( nextCh >= 'A' && nextCh <= 'H' ) {digit = nextCh-'0'-5;}
      else if( nextCh == 'J' || nextCh == 'K' ) {digit = nextCh-'0'-6;}
      else if( nextCh >= 'M' || nextCh <= 'N' ) {digit = nextCh-'0'-7;}	
      else if( nextCh >= 'P' && nextCh <= 'T' ) {digit = nextCh-'0'-8;}
      else if( nextCh >= 'V' && nextCh <= 'Z' ) {digit = nextCh-'0'-9;}

      if (digit >= radix){ 
        error_fatal( ER_LEXDIGITRAD, "LEXICAL", cur_line, cur_column); 
      }
    }//End open if
    if ( isNextNumber() )               {digit = nextCh - '0';}
    if (digit >= radix)
      {error_fatal( ER_LEXDIGITRAD, "LEXICAL", cur_line, cur_column);}
    ext_val = (ext_val*radix) + digit;
    if (ext_val > (LEX_MAXVAL - (nextCh - '0'))/ radix){
      error_fatal(ER_LEXOVERFLOW, "LEXICAL", cur_line, cur_column); 
    }
    nextchar();
  }//End open-while
  return ext_val;
}/*End of extended_num*/

void __number__()
{
  uint32_t radix;
  uint32_t value = ch-'0';	/* Reset value && Quick char-to-num conversion */
  int digit;
  if ( isNextAlpha() )
  {
  error_fatal(ER_UNEXPECTED, "LEXICAL", cur_line, cur_column);
  }
  while ( isNextNumber() ) 
  {/* consume remaining digits */	
    value = (value * 10) + (nextCh - '0');
    if (value > (LEX_MAXVAL - (nextCh - '0'))/ 10)	
    {
      error_fatal(ER_LEXOVERFLOW, "LEXICAL", cur_line, cur_column);
    }
    nextchar();
  }
/***************************************************************************
 EXTENDED NUMBERS */
  if (nextCh == '#')
  {
    if ((value > 32) || (value < 2))
    {
      error_fatal(ER_LEXBADRADIX, "LEXICAL", cur_line, cur_column);
    }
    radix = value;	
    value = 0;
    nextchar();
/*    if (!isNextNumber() || !isNextAlpha())
    {
      error_fatal(ER_EXTDIGMISS, "Extended Numbers", cur_line, cur_column);
    }
*/
    value = __extended_num__(radix);
  }/*End open if*/
/*End Extended
***************************************************************************/

  createLex(lex_next, NUMBER, value, cur_line, cur_column);
}//End __number__

void __unknown__() {
  symbol_start();
  symbol_append(ch);
  while (!isWeird()) {
    nextchar();
    printf("IM SO ANGRY\n\n\n");
    symbol_append(ch);
    break;
  }
  symbol_handle h = symbol_lookup();
  createLex(lex_next, UNKNOWN, h, cur_line, cur_column);
}//End __unknown__

/*******************************************************
 *******************************************************
 *******************************************************/
void lex_open( char * f ) { 
/* initialize subsidiary packages on which we depend
   f pointer to file name or NULL, empty string is equiv to NULL */
  string_init();
  symbol_init();
  /*keyword_init();  We will make this soon! */

  /* open the file */
  if ((f == NULL) || (*f == '\0'))	{infile = stdin;}
  else {
    infile = fopen(f, "r");
    if (infile == NULL) 	        {error_fatal(ER_BADFILE,0);}
  }
  
  cur_column = 1;
  cur_line = 1;
  nextchar();	  /*Have to call both twice to correctly increment*/
  nextchar(); 
  lex_advance(); 
  lex_advance();
}/* End lex_open */


void lex_advance() {
  flopLex( lex_this, lex_next );        /* advance current lexeme */

  while (isWhite() || isComment()){
    if ( isWhite() )                      {__whitespace__();   }
    if ( isComment() )                    { __comment__();     }
  }
  if (lex_this.type == ENDFILE) {
    fclose(infile);
    return;
  }
  if (ch == EOF) {
   lex_next.type = ENDFILE;
   return;
  }
  if      ( isIdent()  )                  { __ident__();       }
  else if ( isNumber() )                  { __number__();      }
  else if ( isString() )                  { __string__();      }
  else if (ISCLASS(ch, PUN) )             { __punctuation__(); }
  else if (ISCLASS(ch, OTH) )             { __unknown__();     }

  nextchar();
}/*End lex_advance()*/

void lex_put( lexeme * lex, FILE * f ) {
  switch (lex->type) {
    case IDENT:
      fprintf(f, "IDENT( %d ",lex->value);
      symbol_put(lex->value, f);
      fprintf(f, ")");
      break;
    case NUMBER:
      fprintf(f, "NUMBER( 10#%d )", lex->value);
      break;
    case STRING:
      fprintf(f, "STRING( %d \"", lex->value);
      symbol_put(lex->value, f);
      fprintf(f, "\" )");
      break;
    case PUNCT:
      fprintf(f, "PUNCT( %d )", lex->value);/*Returns the number of stuff*/
      break;
    case ENDFILE:
      fputs( "ENDFILE", f );
      break;
    case UNKNOWN:
      fprintf( f, "UNKNOWN( ");
      symbol_put(lex->value, f);
      fprintf( f, ")");
    /*case KEYWORD:
      fputs( "KEYWORD", f );
      //printf( "\n%s\n", lex->value);
      break;*/

  }/* End of switch() */
}/* End of lex_put */
