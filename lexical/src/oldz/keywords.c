/* keywords.c	*/
/* implementation of functions declared in keywords.h */

include "keywords.h"

// key_names is used to track all keywords to be added to symboltable upon initialization
const char * const key_names[ KEY_MAX + 1 ] = {
	"end",
        "const",
        "type",
        "exception",
        "var",
        "procedure",
        "function",
        "private",
        "external",
        "enum",
        "array",
        "of",
        "record",
        "if",
        "then",
        "else",
        "select",
        "case",
        "while",
        "do",
        "until",
        "for",
        "in",
        "try",
        "handle",
        "raise",
        "null"
}
// IT IS CRUCIAL that the order of the strings listed in this table
// exactly match the order of the keyword names in the declaration of
// key_handle in file keywords.h

void key_put( key_handle k, FILE * f ) {
        // output the keyword to the human readable file
        fputs( key_names[ k ], f );
}

string_handle key_table[ KEY_MAX + 1 ]

void key_init() {
        // initializer for keyword mechanism
        int i;
        for (i = KEY_MIN; i <= KEY_MAX; i++) {
		key_table[i] = symbol_add( key_names[i] );
	}
}

key_handle key_lookup( symbol_handle s ) {
	// output the keyword handle corresponding to the given symbol handle
	// if the symbol is not a keyword, returns KEY_INVALID

	/*BUG*/ /* stupid version, uses a linear search */
	/* this is initial version taken from lecture notes. */
	/* Final implementation should take advantage of hashing to search for keywords. */


	key_handle i = KEY_MIN;
	while ((i <= KEY_MAX) && (key_table[i] != s)) i++;
	return s;
	// this relies on the fact that KEY_INVALID is KEY_MAX + 1
}

