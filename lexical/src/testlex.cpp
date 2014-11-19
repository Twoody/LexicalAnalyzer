/*
 * Restart of testlex.c
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//#include "config.h"
#include "error.h"
//#include "stringpool.h"
#include "symboltable.h"

#include "lexical.h"

/*
void test();
string_handle add_string(const char *string);
*/

int main( int argc, char * argv[] ) {
  //test();
  lex_open( argv[1] );
  while (!(lex_this.type == ENDFILE)) {
    lex_put( &lex_this, stdout );
    putchar('\n');
    lex_advance();
  }
  lex_put( &lex_this, stdout);
  putchar('\n');
}
