// locale.h : interface specification and configuration for locale.c
//   author : Douglas Jones
//   modified by : members of the Venture group

// locale settings //

#ifndef ERROR_H_
#define ERROR_H_

extern const char *LOC_DEFAULTNAME;
extern const char LOC_FLAGCHAR;

// to encode help messages for various topics
typedef enum help_code {
  HLP_DEFAULT
} help_code;

// print help information for various topics
void print_help(help_code topic);
void print_help();

// error management //

// an enumeration type to encode the error messages
typedef enum error_code {

  // string pool errors
  ER_POOLBOUNDS,
  ER_POOLFULL,

  // symbol table errors
  ER_HASHFULL,

  // lexical errors
  ER_BADFILE,
  ER_LEXEME,
  ER_LEXSTRNL,
  ER_LEXSTREOF,
  ER_LEXUNK,
  ER_LEXOVERFLOW,
  ER_LEXDIGITRAD,
  ER_LEXDIGITBAD,
  ER_LEXBADRADIX,
  ER_EXTDIGMISS,
  ER_LEX_IDENT,
  ER_UNEXPECTED,
  ER_ILLGLPUNCT,
  // kestrel errors
  ER_NOINPUT
} error_code;

// output message to stderr and exit the program indicating failure
void error_fatal( error_code er, const char *origin, int line, int col );
void error_fatal( error_code er, const char *origin );
void error_fatal( error_code er );

// output message to stderr without exiting the program
void error_warn( error_code er, const char *origin, int line, int col );
void error_warn( error_code er, const char *origin );
void error_warn( error_code er );

#endif /* ERROR_H  */
