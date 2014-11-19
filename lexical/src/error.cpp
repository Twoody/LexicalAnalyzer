/*
 *Restart of error.c
 */

// locale.cpp : locale management for Kestrel compiler
//   author : Douglas Jones
//   modified by : members of the Venture group
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "error.h"

// locale management //
const char *LOC_DEFAULTNAME = "kestrel";
const char LOC_FLAGCHAR = '-';

// this array should have help messages corresponding to members of help_code
static const char *help_message[] ={
  "brb after crashing and burning", // H_DEFAULT
};


// help messages
void print_help( help_code topic ) {
  printf("%s\n", help_message[topic]);
}

void print_help() {
  printf("%s\n", help_message[HLP_DEFAULT]);
}

// error management //

// this array must have on eentry for each member of the error_code 
//   enumeration (in errors.h) in exactly the same order
// used in calls to error_fatal()
static const char *error_message[] = {
  // string pool errors
  "Pool received a handle past the end of the pool.", // ER_POOLBOUNDS
  "Pool is full, please go swimming elsewhere.", // ER_POOLFULL

  // symbol table errors
  "Tried to add a symbol but the hash table is full.", // ER_HASHFULL

  // lexical errors
  "Cannot open input file.", // ER_BADFILE
  "Encountered an unexpected lexeme.", // ER_LEXEME
  "Encountered new line while reading string literal.", // ER_LEXSTRNL
  "Reached end of file while reading string literal.", // ER_LEXSTREOF
  "Encountered an unknown character.", // ER_LEXUNK
  "Number overflowed during accumulation.", // ER_LEXOVERFLOW
  "Digit larger than radix.", // ER_LEXDIGITRAD
  "Couldn't decode digit.", // ER_LEXDIGITBAD
  "Unsupported radix.", // ER_LEXBADRADIX
  "Expected digits after '#'." // ER_EXTDIGMISS
  "Character cannot be in an identifier." //ER_LEX_IDENT
  "Unexpected character." //ER_UNEXPECTED
  "This isn't a recgonized PUNCT" //ER_ILLGLPUNCT
  // kestrel errors
  "No input files." // ER_NOINPUT
};
  
// fatal errors
void error_fatal( error_code er, const char *origin, int line, int col ) {
  fprintf( stdout, "[%s] Fatal error (line %d, col %d): %s\n", origin, line, col, error_message[ er ] );
  exit( EXIT_FAILURE );
}

void error_fatal( error_code er, const char *origin ) {
  fprintf( stdout, "[%s] Fatal error: %s\n", origin, error_message[ er ] );
  exit( EXIT_FAILURE );
}

void error_fatal( error_code er) {
  fprintf( stdout, "Fatal error: %s\n", error_message[ er ] );
  exit( EXIT_FAILURE );
}

// warnings
void error_warn( error_code er, const char *origin, int line, int col) {
  fprintf( stdout, "[%s] Warning (line %d, col %d): %s\n", origin, line, col, error_message[er]);
}

void error_warn( error_code er, const char *origin) {
  fprintf( stdout, "[%s] Warning: %s\n", origin, error_message[er]);
}

void error_warn( error_code er) {
  fprintf( stdout, "Warning: %s\n", error_message[er]);
}
