/* keywords.h	*/

/* this header file must include:
	stringpool.h
	symboltable.h
*/

/* by: Bryan Oswald -- created: 11/6/2014 */

enum key_handle { // a list of all the keywords in the language
	key_END,
        key_CONST,
        key_TYPE,
        key_EXCEPTION,
        key_VAR,
        key_PROCEDURE,
        key_FUNCTION,
        key_PRIVATE,
        key_EXTERNAL,
        key_ENUM,
        key_ARRAY,
        key_OF,
        key_RECORD,
        key_IF,
        key_THEN,
        key_ELSE,
        key_SELECT,
        key_CASE,
        key_WHILE,
        key_DO,
        key_UNTIL,
        key_FOR,
        key_IN,
        key_TRY,
        key_HANDLE,
        key_RASIE,
        key_NULL
}
// any additions to this enumeration must adjust KEY_MAX accordingly and
// IT IS CRUCIAL that the order of the keyword names listed in this table
// exactly match the order of the keyword strings in the initialization of
// key_names in file keywords.c

#define KEY_MIN key_END
#define KEY_MAX key_NULL
#define KEY_INVALID (KEY_MAX + 1)

void key_init();
// initializer for keyword mechanism

void key_put( key_handle k, FILE * f );
// output the keyword to the human readable file

key_handle key_lookup( symbol_handle s );
// output the keyword handle corresponding to the given symbol handle
// if the symbol is not a keyword, returns KEY_INVALID

