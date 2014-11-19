/*
 * Restart of stringpool.cpp
 * User interface specifications for the string pool.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
//#include "error.h"
#include "config.h"

#define EXTERN
#include "stringpool.h"
#include "error.h"

/*
typedef uint32_t string_handle;
// the string handle type.  C and C++ do not let us be
// more specific, but it is actually values between
// 0 and POOL_SIZE-1, inclusive.

EXTERN char _string_pool[ POOL_SIZE ];
// private, the actual location where the text of strings is stored

EXTERN string_handle _string_limit;
// private, index of the first unused location in _string_pool

EXTERN string_handle _string_pos;
// private, position to store new characters added to _string_pool
*/


void string_put ( string_handle handle, FILE *f )
{
	check_bounds(handle);
	if (f == NULL) { f = stdout; }
	while ( ( _string_pool[handle] != '\0' )&&( handle < _string_limit  ) )
	{
		fputc(_string_pool[handle++], f);
	}
}/* End string_put() */

int string_eq( string_handle h1, string_handle h2 )
{
	check_bounds(h1);
	check_bounds(h2);
	for (; _string_pool[h1] == _string_pool[h2]; h1++, h2++){
		if (_string_pool[h1] == '\0'){return 0;}
	}
	return _string_pool[h1]-_string_pool[h2];
}
/* compare the strings h1 and h2, returns true if they have identical text */

int string_len(string_handle h )
{
	check_bounds(h);
	int len = 0;
	while (_string_pool[h+len] != '\0'){len++;}
	return len;
}


