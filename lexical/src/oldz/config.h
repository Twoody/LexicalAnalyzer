// config.h

// compiler configuration

// maximum number of distinct symbols (identifiers and keywords) allowed
#define SYMBOL_SIZE 100

// number relatively prime to symbol size
#define SYMBOL_HASH 11

// maximum number of chars in the set of distinct symbols
#define POOL_SIZE (SYMBOL_SIZE * 8)

// maximum value an integer lexeme is allowed to be
#define LEX_MAXVAL UINT32_MAX