/* sample.c */

/* written by Douglas Jones, July 2010,
   based on pieces of cruncher,
     written in Pascal by Douglas Jones, March 1990
     rewritten in C, Jan 2007
*/

/* Output a random derivation from the grammar */

#include <stdlib.h>
#include <stdio.h>

#include "grammar.h"
#include "writetool.h"
#include "sample.h"

/*
 * printing utility
 */

static void outsym( PSYMBOL s ); /* forward declaration */

static void outprod( PPRODUCTION p ) { /* put the symbols on RHS of rule p */
        PELEMENT e;
	PSYMBOL s;

	if (p != NULL) { /* empty rules should never happen, but be safe */
		e = p->data;
		while (e != NULL) {
			s = e->data;
			if (s != emptypt) outsym( s );

			e = e->next;
		}
	}
}

static void outsym( PSYMBOL s ) { /* output a symbol or pick a rule */
	PPRODUCTION p;
	int pcount;
	int pnum;

	if (TERMINAL(s)) {
		outspacesym( s, 1, ' ' );
		outsymbol( s );
	} else { /* nonterminal symbol */

		/* how many alternatives are there? */
		pcount = 0;
		for (p = s->data; p != NULL; p = p->next) pcount++;

		/* pick an alternative */
		p = s->data;
		for (pnum = random() % pcount; pnum > 0; pnum--) {
			p = p->next;
		}

		/* output that alternative */
		outprod( p );
	}
}

/*
 * The interface
 */

void sample() { /* write a sample string generated by grammar */
	outsetup();
	srandom( time( NULL ) );
	if (head != NULL) { /* there is a distinguished symbol */
		outsym( head );
	}
	outline();
}
