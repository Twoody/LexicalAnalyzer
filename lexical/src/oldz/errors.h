// errors.h
#ifndef ERRORS_H
#define ERRORS_H

// an enumeration type to encode the error messages
typedef enum error_message 
{
	// intended for use in calls to error_fatal
	ER_BADFILE,
	ER_POOLFULL,
	ER_TABLEFULL,
	ER_LEXVAL_MAX,
	ER_MAXRADIX,
    EXPECTED_DIG_GOT_LET,
    ILGL_NOTATION,
    ER_EXTDIGMISS,
    ER_DIGOUTOFRANGE,
    ER_EXPECTSTRINGGOTEOF,
    ER_POOLBOUNDS,


	/*BUG*/ // more things go here

}//End of error_message
error_message;


void error_fatal( error_message er, int line );
// output message er and exit the program indicating failure

#endif /* ERRORS_H */
