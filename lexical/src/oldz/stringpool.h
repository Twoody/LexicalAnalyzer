// stringpool.h
#ifndef STRINGPOOL //header guard
#define STRINGPOOL


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "errors.h"
#include "config.h"

#ifndef EXTERN
	#define EXTERN extern
#endif

typedef uint32_t string_handle;
// the string handle type.  C and C++ don't let us be
// more specific, but it is actually values between
// 0 and POOL_SIZE-1, inclusive.

EXTERN char _string_pool[ POOL_SIZE ];
// private, the actual location where the text of strings is stored

EXTERN string_handle _string_limit;
// private, index of the first unused location in _string_pool

EXTERN string_handle _string_pos;
// private, position to store new characters added to _string_pool

#define STRING_NULL 0
// the null string, never used to index an actual string

//void string_init();
#define string_init() { _string_limit = 1; }
// initializer for the string pool package
// initial value 1 guarantees that STRING_NULL won't accidentally be used

//string_handle string_start();
#define string_start() ( _string_pos = _string_limit, _string_limit )
// setup to accumulate a new string and return its handle

//void string_append( char ch );
#define string_append(ch) {                                             \
        if (_string_pos > (POOL_SIZE - 1)) error_fatal( ER_POOLFULL, 1);  \
        _string_pool[ _string_pos ] = ch;                               \
        _string_pos++;                                                  \
}
// append one character to the string

//void string_done();
#define string_done() {                                                 \
        if (_string_pos > (POOL_SIZE - 1)) error_fatal( ER_POOLFULL, 1);  \
        _string_pool[ _string_pos ] = '\0';                             \
        _string_pos++;                                                  \
}
// mark the end of the string

//void string_accept();
#define string_accept() { _string_limit = _string_pos; }
// accept the new string as a permanent part of the string pool

//void string_reject();
#define string_reject() { _string_pos = _string_limit; }
// reject the new string, it will not be included in the string pool

#define string_pool_full() (_string_pos >= (POOL_SIZE - 2))


#define string_adding() (_string_pos > _string_limit)


#define check_bounds(h) {if (h > POOL_SIZE - 1) error_fatal(ER_POOLBOUNDS, 0);}


void string_put( string_handle h, FILE * f );
// output the string to the human-readable file

int string_eq( string_handle h1, string_handle h2 );
// compare the strings h1 and h2, returns true if they have identical text

// returns the length of the string h1
int string_len( string_handle h);

/*
 *  note:
 *  to add a string to the pool
 *    handle = string_start()
 *     for each character ch in the string { string_append(ch) }
 *       string_done()
 *       if symbol_table_lookup_fails() {
 *         string_accept()
 *         symbol_table_add( handle )
 *       } else {
 *           string_reject()
 *       }     
 */

#undef EXTERN

//end header guard
#endif