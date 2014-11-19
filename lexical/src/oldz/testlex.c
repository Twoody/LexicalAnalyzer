// testlex.c -- test framework for lexical analyzer
//   author: Douglas W. Jones

// testlex infile -- processes data from infile

#include <stdio.h>
#include <stdint.h>

#include <unistd.h>

/*BUG*/ // need to do things expected by lexical.h 
#define EXTERN
#include "config.h"
#include "locale.h"
#include "stringpool.h"

#include "lexical.h"
int main( int argc, char * argv[] ) {
    
    lex_open( argv[1] );

	while (!lex_this.type == ENDFILE)
	{
		lex_put( &lex_this, stdout );
		fputc(' ', stdout);
		lex_advance();
		printf("\n");
		sleep(1);
	}
	lex_put (&lex_this, stdout);
	putchar('\n');
}

