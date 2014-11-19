/* errors.c */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#define STATIC
#include "errors.h"

// the error messages.
// NOTE:  this array must have one entry for each
// member of the error_message enumeration, in exactly the same order
static const char * message[] = {
	// intended for use in calls to error_fatal
	/* ER_BADFILE  */ "Cannot open input file.",
	/* ER_POOLFULL */ "String pool is full.",
	/* ER_TABLEFULL*/ "Symbol table is full.",
	/* ER_LEXVAL_MAX*/ "Integer exceeds maximum value.",
	/* ER_MAXRADIX */  "Maximum integer radix exceeded.",
	/* EXPECTED_DIG_GOT_LET */ "Expected a digit but got a letter",
	/* ILGL_NOTATION */ "Illegal notation",
	/* ER_EXTDIGMISS */ "Missing extended digit",
	/* ER_DIGOUTOFRANGE */ "Input digit exceeds radix",
	"STRING POOL: POOLBOUNDS"
        /*BUG*/ // Need more other messages go.
        //Since we are not there yet, this can wait.
};

void error_fatal( error_message er, int line ) {
	// output the message er and exit the program indicating failure
	fprintf( stderr, "Fatal error on line %d: %s\n", line, message[ er ] );
	exit( EXIT_FAILURE );
}

/*
int main() {
  error_fatal(ER_BADFILE, 5);
}
*/
