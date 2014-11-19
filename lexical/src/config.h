/*
 * Restart of config.h
 * compiler configuration
 */


// number relatively prime to symbol size
#define SYMBOL_HASH 64       // Why not?
#define SYMBOL_SIZE 100001     // Maximum number of distinct identifiers and keywords allowed; Should be larger
#define SYMBOL_ILLEGAL -1    // A flag that we can use anytime


// maximum number of chars in the set of distinct symbols
#define POOL_SIZE 32768     //Use to be 32 Kilobytes(32768 bytes); Now 10MBs(10485760bytes)


// maximum value an integer lexeme is allowed to be

// lexical
#define LEX_MAXVAL 0x7FFFFFFF
#define LEX_MINVAL 0x80000000
#define LEX_MINRAD 2
#define LEX_MAXRAD 32
