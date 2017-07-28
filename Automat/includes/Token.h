#ifndef TTYPES_H_
#define TTYPES_H_

#include <cstring>
#include <iostream>
using namespace std;

enum TType {
	ERROR 						= 0,	// Falsche Eingabe
	INTEGER						= 1,	// Zahlen
	IDENTIFIER 					= 2,	// Bezeichner
	SIGN_PLUS 					= 3,	// +
	SIGN_MINUS 					= 4,	// -
	SIGN_MULTIPLIER 			= 5,	// *
	SIGN_COLON 					= 6,	// :
	SIGN_GREATER 				= 7,	// >
	SIGN_SMALLER 				= 8,	// <
	SIGN_EQUAL 					= 9,	// =
	SIGN_AND 					= 10,	// &&
	SIGN_SEMICOLON 				= 11,	// ;
	SIGN_BRACKET_ON 			= 12, 	// (
	SIGN_BRACKET_CLOSE 			= 13, 	// )
	SIGN_CURLY_BRACKET_ON 		= 14, 	// {
	SIGN_CURLY_BRACKET_CLOSE 	= 15, 	// }
	SIGN_SQUARE_BRACKET_ON 	  	= 16, 	// [
	SIGN_SQUARE_BRACKET_CLOSE 	= 17, 	// ]
	SIGN_SPECIAL 				= 18, 	// <:>
	SIGN_COLON_EQUAL 			= 19, 	// :=
	SIGN_EXCLEMATION 			= 20,	// !
	COMMENT 					= 21,	// Kommentare
	TOKEN_IF 					= 22, 	// IF || if
	TOKEN_WHILE 				= 23, 	// WHILE || while
	TOKEN_SPACE 				= 24, 	// _
	IGNORE 						= 25, 	// Kommentar oder Space
	CONTINUE					= 26, 	// Mögliche Eingabe
	ERROR_SPECIAL 				= 27, 	// Wenn <:
	LINE_BREAK					= 28,	// Special Character: Line Break
	ERROR_AND					= 29,
	END_OF_FILE					= 30
};

class Token {
private:
	TType type;
	char* typeName;
	int line;
	int column;
	char* lexem;
	int value;

public:
	Token(TType type, char* lexem, int line, int column);
	~Token();
	TType getType();
	char* getTypeName();
	char* getLexem();
	int getLine();
	int getColumn();
	int getValue();

};


#endif /* TTYPES_H_ */
