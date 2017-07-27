#ifndef AUTOMAT_H_
#define AUTOMAT_H_
#include <cstring>
#include <iostream>

#include "Token.h"

using namespace std;

enum States {
	START_STATE 		 	= 0,
	IDENTIFIER_STATE 	 	= 1,
	INT_STATE			 	= 2,
	SIGN_STATE			 	= 3,
	EQUAL_STATE			 	= 4,
	COLON_STATE			 	= 5,
	COMMENT_STATE			= 6,
	COMMENT_END_BEGIN_STATE = 7,
	COMMENT_END_STATE 	 	= 8,
	EQUAL_COLON_STATE 	 	= 9,
	SPECIAL_STATE		 	= 10,
	COLON_EQUAL_STATE 	 	= 11,
	SPACE_STATE			 	= 12,
	AND_STATE			 	= 13,
	AND_AND_STATE		 	= 14
};

class Automat {
private:
	States state;
	char sign;

public:

	Automat();
	~Automat();

	TType proofInput(char input);

	TType proofStartState(char input);

	TType proofIdentifierState(char input);

	TType proofIntState(char input);

	TType proofSignState();

	TType proofEqualState(char input);

	TType proofColonState(char input);

	TType proofCommentState(char input);

	TType proofCommentEndBeginState(char input);

	TType proofCommentEndState(char input);

	TType proofEqualColonState(char input);

	TType proofSpecialState(char input);

	TType proofColonEqualState(char input);

	TType proofSpaceState(char input);

	TType proofAndState(char input);

	TType proofAndAndState(char input);

	TType getSign(char input);

};


#endif /* AUTOMAT_H_ */
