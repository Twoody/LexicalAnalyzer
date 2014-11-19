/* lexical.c
 *    Kestrel lexical analyzer interface spec
 *       by D.W.Jones
 *
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "config.h"
#include "stringpool.h"
#include "symboltable.h"
#include "errors.h"

#define EXTERN
#include "lexical.h"

FILE *infile; 		/* Lets declare that we use a file!!!            */
int ch; 		/* The current character (type char) or EOF      */
int nextCh;             /* The character following the current character */
int value;		
lexeme lex_this;
lexeme lex_next;
int cur_column;
int cur_line;
int let_count;
/*Moved this to lex.h -> #define ISCLASS(ch,class) (char_class[ch]&(class))*/

#define nextChar() { 		\
	ch = nextCh;		\
	nextCh = getc(infile);	\
	cur_column +=1;		\
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
        /* beyond ASCII 						  */
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
           OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH
};

/*************************************************************************
 * LINK: http://homepage.cs.uiowa.edu/~jones/compiler/spring13/notes/06.shtml
 * **************************************************************************/
int __punct_type__()
{
	switch (ch)
	{
		case '=': return PT_EQUALS; break;                      /* = */
		case ':': return PT_COLON;  break;                      /* : */
		case '(': return PT_LPAREN; break;                      /* ( */
		case ')': return PT_RPAREN; break;                      /* ) */
		case '[': return PT_LBRAKT; break;                      /* [ */
		case ']': return PT_RBRAKT; break;                      /* ] */
		case '{': return PT_LBRACE; break;                      /* { */
		case '}': return PT_RBRACE; break;                      /* } */
		case ',': return PT_COMMA;  break;                      /* , */
		case '@': return PT_ATSIGN; break;                      /* @ */
		case '+': return PT_PLUS;   break;                      /* + */
		case '-': return PT_MINUS;  break;                      /* - */
		case '*': return PT_TIMES;  break;                      /* * */
		case '/': return PT_DIV;    break;                      /* / */
		case '&': return PT_AND;    break;                      /* & */
		case '|': return PT_OR;     break;                      /* | */
		case ';': return PT_SEMIC;  break;                      /* ; */
		case '~': return PT_TILDE;  break;                      /* ~ */
		case '<':
			if (nextCh == '>') { nextChar()  return PT_NOTEQL; }            /* <> */
			if (nextCh == '=') { nextChar()  return PT_LE;     }            /* <= */
			ch = '<';
			return PT_LT;    break;        /* <  */
		case '>':
			if (nextCh == '=') { nextChar() return PT_GE; }                 /* >= */
			ch = '>';
			return PT_GT;     break;        /* >  */
		case '.':
			if (nextCh == '.') { nextChar()  return PT_ELIPS; }             /* .. */
			ch = '.';
      return PT_DOT;   break;        /* .  */
		default: return -1;
	}/* End of swich(ch)  */
	createLex(lex_next, PUNCT, (int) ch, cur_line, cur_column);
}/* End of get_punct_type()  */

int __extended_num__(int radix)
{
	value = 0;
	int digit;
	while (ISCLASS(ch, (LET | DIG)) ) 	
	{										
		if(ISCLASS(ch, LET))
		{    /* If alpha, then convert to digit */
			if     ( ch == 'l' || ch == 'L' ) { digit = 1; }
			else if( ch == 'i' || ch == 'I' ) { digit = 1; }
			else if( ch == 'o' || ch == 'O' ) { digit = 0; }
			else if( ch == 'u' || ch == 'U' ) { digit = 32;} 
			/*BUG Talk to Jones about u & U */

/* Now we need to check if character is lower or upper for proper mathz */

/*LOWER --Math can be seen via ASCII table, and the jumps in the alphabet
*******************************************************************/
			else if( ch >= 'a' && ch <= 'h' ) {digit = ch-'0'-37;}
			else if( ch == 'j' || ch == 'k' ) {digit = ch-'0'-38;}	
			else if( ch >= 'm' || ch <= 'n' ) {digit = ch-'0'-39;}
			else if( ch >= 'p' || ch <= 't' ) {digit = ch-'0'-40;}
			else if( ch >= 'v' || ch <= 'z' ) {digit = ch-'0'-41;}
/*End LOWER					
******************************************************************/

/*UPPER		Logic same as above		
******************************************************************/
			else if( ch >= 'A' && ch <= 'H' ) {digit = ch-'0'-5;}
      else if( ch == 'J' || ch == 'K' ) {digit = ch-'0'-6;}
			else if( ch >= 'M' || ch <= 'N' ) {digit = ch-'0'-7;}	
			else if( ch >= 'P' || ch <= 'T' ) {digit = ch-'0'-8;}
			else if( ch >= 'V' || ch <= 'Z' ) {digit = ch-'0'-9;}
/*END UPPER					
*******************************************************************/
			if (digit > radix) 
			{ 
				error_fatal( ER_DIGOUTOFRANGE, cur_line);
			} /* fatal error if digit is larger than radix */
			value = (value*radix) + digit;
		}/*End of extended digit*/

		if (value > (LEX_MAXVAL - (ch - '0'))/ radix) 
		{
			error_fatal(ER_LEXVAL_MAX, cur_line); 
		}
		nextChar();
	}/*End open-while*/
}/*End of extended_num*/

void __comment__(){
	nextChar();
	while ( ch != '\n' && ch!=EOF ) { nextChar() }
                                 /* If newline, the comment is done */
}/*End __comment__()*/

void isComment(){
	if (ch=='-' && nextCh=='-'){__comment__();}
}

void __ident__()
{
	symbol_start();  	              /* reset _symbol_hash to 0 */
	symbol_append(ch);              /* append first element */
	nextChar();
	int id_val = symbol_lookup();
	while (ISCLASS(ch, (LET | DIG)))
	{
	symbol_append(ch);              /* eat all of the letters and numbers */
	nextChar();
	}
	if ( !ISCLASS(ch, (LET|DIG)) )
	{
		/*BUG   expect but got*/
	}
	string_done();                  /* mark end of string */
	createLex(lex_next, IDENT, id_val, cur_line, cur_column);
}/*End __ident__()*/


char digit_of_char(char ch)
{
  if (ISCLASS(ch, DIG))
    return ch - '0';
  else if (ISCLASS(ch, LET)) {
    if ((ch == 'o') || (ch == 'O')) return 0;
    if ((ch == 'i') || (ch == 'I') || (ch == 'l') || (ch == 'L')) return 1;
    if ((ch == 'u') || (ch == 'U')) return 36;

    char val = 10 + ch - ((ch >= 'a') ? 'a' : 'A');
    val -= (val > 17) + (val > 20) + (val > 23) + (val > 29);
    return val;
  }
}

uint32_t __extendedNum__(uint32_t radix) {
  bool baddigit=false;
  bool overflow=false;
  char digit;
  uint32_t value = 0;
  if ((radix < 2) || (radix > 32)){
    /*error_warn(ER_LEXBADRADIX, "Lexical", cur_line, cur_column);*/
  }
  while (ISCLASS(nextCh, DIG | LET)) {
    nextChar();
    digit = digit_of_char(ch);
    baddigit = baddigit | (digit >= radix);
    overflow = overflow || (value > (LEX_MAXVAL - digit) / radix);
    value = (value * radix) + digit;
  }

/*
  if (baddigit) error_warn(ER_LEXDIGITRAD, "Lexical", cur_line, ruc_column);
  if (overflow) error_warn(ER_LEXOVERFLOW, "Lexical", cur_line, cur_column);
*/
  return value;
}/* end __extendedNum__()  */

void __number__()
{
  bool baddigit;
  bool overflow = false;
  char digit;
  uint32_t radix = 10;

  printf("I'm all up in here\n\n");

  uint32_t value;      /* Quickchar-to-num conversion  */

  while (ISCLASS(ch, DIG) || nextCh == '#' )
  {/* consume remaining digits */
    if (nextCh == '#'){
      nextChar();
      value = __extendedNum__(value);
      break;
    }
    nextChar();
    digit = digit_of_char(ch);
    baddigit = baddigit || (digit >= radix);
    overflow = overflow || (value > ((LEX_MAXVAL - digit)/radix));
    value = (value*radix)+digit;
  }/*end while*/
  createLex(lex_next, NUMBER, value, cur_line, cur_column);
/*
  if (baddigit) error_warn(ER_LEXDIGITRAD, "Lexical", cur_line, cur_column);
  if (overflow) error_warn(ER_LEXOVERFLOW, "Lexical", cur_line, cur_coumnl);

			error_fatal(ER_MAXRADIX, cur_line);
			error_fatal(ER_EXTDIGMISS, cur_line);
*/

}/*End __number__ */

void __string__()
{
	int openingQuote = ch;
	int let_count = 0;
	nextChar();                     /*Skip the first quote */
	symbol_start();                 /*Call to symboltable.h */

/* Consume the string until we get an EOF or the closing quote */
	while ((ch != openingQuote) && (ch != EOF))
	{
		symbol_append(ch);
		nextChar();
		let_count++;
	}
	if (ch == EOF)
	{
		error_fatal( ER_EXPECTSTRINGGOTEOF, cur_line );
	}
	else
	{
		string_done();
		lex_next.value = symbol_lookup();
	}
	createLex(lex_next, STRING, let_count, cur_line, cur_column);
}/*End __string__*/

void __punctuation__()
{/*Uses punct_type above; returns -1 if not in table*/
	
	lex_next.value = __punct_type__();
	if (lex_next.value == -1)
		createLex(lex_next, PUNCT, 777, cur_line, cur_column);
}/*End __punctuation__*/

void __unknown__() {
	symbol_start();
	symbol_append(ch);
	while (char_class[nextCh] == OTH) 
	{
		nextChar();
		symbol_append(ch);
	}
	symbol_handle h = symbol_lookup();
	createLex(lex_next, UNKNOWN, h, cur_line, cur_column);
}

void __whitespace__() {
  while (ISCLASS(ch, WIT))
  {
    if (ch =='\n') 
    {
      cur_line +=1;
      cur_column = 0;
    }
    else if (ch == '-')
    {
      __comment__();
    }
    nextChar();
  }/* end while */
}/* end __whitespace__ */

/*******************************************************
 *******************************************************
 ********************************************************/
void lex_open( char * f ) { /*CHANGED from `const char` */
	/* initialize subsidiary packages on which we depend
 * 	   f pointer to file name or NULL, empty string is equiv to NULL*/
	string_init();
	symbol_init();
	/*keyword_init();  We will make this soon! */

	/* open the file */
	if ((f == NULL) || (*f == '\0'))	{infile = stdin;}
	else {
		infile = fopen(f, "r");
		if (infile == NULL) 	{error_fatal(ER_BADFILE,0);}
	}
  
	cur_column = 1;
	cur_line = 1;
	nextChar();	/*Have to call twice to correctly increment*/
	nextChar(); 
	lex_advance(); 
	lex_advance();
}/* End lex_open */

void lex_advance() {
  flopLex( lex_this, lex_next );        /* advance current lexeme */

  if (lex_this.type == ENDFILE) {
    fclose(infile);
    return;
  }
  if (ch == EOF) {
   lex_next.type = ENDFILE;
   return;
  }
  __whitespace__();

  if ( ch == '-' )                        { __comment__();     }
  else if (ISCLASS(ch, LET))              { __ident__();       }
  else if (ISCLASS(ch, DIG))              { __number__();      }
  else if ((ch == '"') || (ch == '\''))   { __string__();      }
  else if ( ISCLASS(ch, PUN) )            { __punctuation__(); }	
  else if (ISCLASS(ch, OTH) )             { __unknown__();     }

	nextChar();
}/*End lex_advance()*/

void lex_put( lexeme * lex, FILE * f ) {
	switch (lex->type) {
		case IDENT:
			fprintf(f, "IDENT( ");
			fprintf(f, "%d", lex->value);
			symbol_put(lex->value, f)
			fprintf(f, " )");
			break;
		case KEYWORD:
			fputs( "KEYWORD", f );
			/*printf( "\n%s\n", lex->value);*/
			break;
		case NUMBER:
			fprintf(f, "NUMBER( 10#%d )", lex->value);
			break;
		case STRING:
			fprintf(f, "STRING( \"%d\" )", lex->value);
			symbol_put(lex->value, f);
			break;
		case PUNCT:
			fprintf(f, "PUNCT( %s )", lex->value);
			break;
		case ENDFILE:
			fputs( "ENDFILE", f );
			break;
		case UNKNOWN:
			fprintf( f, "UNKNOWN( ");
			symbol_put(lex->value, f);
			fprintf( f, " )");
  	}
}
