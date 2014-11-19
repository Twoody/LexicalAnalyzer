//symboltable.c:	By D.W.Jones
//  implementation of the symbol table
//  (although much of it was implemented in the header file)

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "config.h"
#include "stringpool.h"

#ifndef EXTERN
    #define EXTERN
#endif

#include "symboltable.h"
#include "errors.h"


void symbol_init() {
//_symbol_table = (string_handle*)calloc(SYMBOL_SIZE, sizeof(string_handle));
	int i;
	for (i = 0; i < SYMBOL_SIZE; i++){
	_symbol_table[i] = STRING_NULL;
	}
}

symbol_handle symbol_define(const char *s){
  symbol_start();
  while(*s != '\000'){
    symbol_append(*s);
    s++;
  }
  return symbol_lookup();
}

symbol_handle symbol_lookup() {
 	string_done();
	symbol_handle place = _symbol_hash;

	for (;;) 
	{ /* loop exits by embedded returns */
		if (_symbol_table[ place ] == STRING_NULL ) 
		{	// add symbol to table
			_symbol_table[ place ] = _symbol_string;
			string_accept();
			return place;
		}
		if (string_eq(_symbol_table[ place ], _symbol_string )) 
		{
			// symbol is already in table
			string_reject();
			return place;
		}
		place = place + 1;
		if (place == SYMBOL_SIZE) place = 0; 
		if (place == _symbol_hash) { error_fatal(ER_TABLEFULL, 1);}
	}
}
