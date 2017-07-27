#include <iostream>

using namespace std;

#include "../includes/Automat.h"

#include "../includes/Token.h"

	Automat::Automat() {
		this->state = START_STATE;
		this->sign = '\0';
	}

	Automat::~Automat() {
	}

	TType Automat::proofInput(char input) {
		switch (this->state) {
			case START_STATE			: return proofStartState(input);
			case IDENTIFIER_STATE		: return proofIdentifierState(input);
			case INT_STATE				: return proofIntState(input);
			case SIGN_STATE				: return proofSignState();
			case EQUAL_STATE			: return proofEqualState(input);
			case COLON_STATE			: return proofColonState(input);
			case COMMENT_STATE			: return proofCommentState(input);
			case COMMENT_END_BEGIN_STATE: return proofCommentEndBeginState(input);
			case COMMENT_END_STATE		: return proofCommentEndState(input);
			case EQUAL_COLON_STATE		: return proofEqualColonState(input);
			case SPECIAL_STATE			: return proofSpecialState(input);
			case COLON_EQUAL_STATE	 	: return proofColonEqualState(input);
			case SPACE_STATE 			: return proofSpaceState(input);
			case AND_STATE			 	: return proofColonEqualState(input);
			case AND_AND_STATE 			: return proofSpaceState(input);
			default: return ERROR;
		}
	}

	TType Automat::proofStartState(char input) {
		if ((input >= 'a' && input <= 'z')
			|| (input >= 'A' && input <= 'Z')) {
			this->state = IDENTIFIER_STATE;
			return CONTINUE;
		}
		if (input >= '0' && input <= '9') {
			this->state = INT_STATE;
			return CONTINUE;
		}

		switch (input) {
			case '=':
				this->state = EQUAL_STATE;
				return CONTINUE;
			case ':':
				this->state = COLON_STATE;
				return CONTINUE;
			case '&':
				this->state = AND_STATE;
				return CONTINUE;
			case '+':
			case '-':
			case '*':
			case '<':
			case '>':
			case '!':
			case ';':
			case '(':
			case ')':
			case '{':
			case '}':
			case '[':
			case ']':
				this->sign = input;
				this->state = SIGN_STATE;
				return CONTINUE;
			case ' ':
			/*********/
			case '\t':
			case '\b':
			case '\r':
			case '\f':
			/*********/
				this->state = SPACE_STATE;
				return IGNORE;
		}

		if(input == '\n') {
			this->state = START_STATE;
			return LINE_BREAK;
		}

		return ERROR;
	}

	TType Automat::proofIdentifierState(char input) {
		if ((input >= 'a' && input <= 'z')
			|| (input >= 'A' && input <= 'Z')
			|| (input >= '0' && input <= '9')) {
			return CONTINUE;
		}
		this->state = START_STATE;
		return IDENTIFIER;
	}

	TType Automat::proofIntState(char input) {
		if (input >= '0' && input <= '9') {
			return CONTINUE;
		}
		this->state = START_STATE;
		return INTEGER;
	}

	TType Automat::proofSignState() {
		this->state = START_STATE;
		switch (this->sign) {
			case '+':
				return SIGN_PLUS;
			case '-':
				return SIGN_MINUS;
			case '*':
				return SIGN_MULTIPLIER;
			case '<':
				return SIGN_SMALLER;
			case '>':
				return SIGN_GREATER;
			case '!':
				return SIGN_EXCLEMATION;
			case ';':
				return SIGN_SEMICOLON;
			case '(':
				return SIGN_BRACKET_ON;
			case ')':
				return SIGN_BRACKET_CLOSE;
			case '{':
				return SIGN_CURLY_BRACKET_ON;
			case '}':
				return SIGN_CURLY_BRACKET_CLOSE;
			case '[':
				return SIGN_SQUARE_BRACKET_ON;
			case ']':
				return SIGN_SQUARE_BRACKET_CLOSE;
			default:
				return ERROR;
		}
	}

	TType Automat::proofEqualState(char input) {
		switch (input) {
			case ':':
				this->state = EQUAL_COLON_STATE;
				return CONTINUE;
			default:
				this->state = START_STATE;
				return SIGN_EQUAL;
		}
	}

	TType Automat::proofColonState(char input) {
		switch (input) {
			case '*':
				this->state = COMMENT_STATE;
				return IGNORE;
			case '=':
				this->state = COLON_EQUAL_STATE;
				return CONTINUE;
			default:
				this->state = START_STATE;
				return SIGN_COLON;
		}
	}

	TType Automat::proofCommentState(char input) {
		switch (input) {
			case '*':
				this->state = COMMENT_END_BEGIN_STATE;
				return CONTINUE;
			default:
				return IGNORE;
		}
	}

	TType Automat::proofCommentEndBeginState(char input) {
		switch (input) {
			case ':':
				this->state = COMMENT_END_STATE;
				return CONTINUE;
			default:
				this->state = COMMENT_STATE;
				return IGNORE;
		}
	}

	TType Automat::proofCommentEndState(char input) {
		this->state = START_STATE;
		return COMMENT;
	}

	TType Automat::proofEqualColonState(char input) {
		switch (input) {
			case '=':
				this->state = SPECIAL_STATE;
				return CONTINUE;
			default:
				return ERROR_SPECIAL;
		}
	}

	TType Automat::proofSpecialState(char input) {
		this->state = START_STATE;
		return SIGN_SPECIAL;
	}

	TType Automat::proofColonEqualState(char input) {
		this->state = START_STATE;
		return SIGN_COLON_EQUAL;
	}

	TType Automat::proofSpaceState(char input) {
		switch (input) {
			case ' ':
				return IGNORE;
			default:
				this->state = START_STATE;
				return TOKEN_SPACE;
		}
	}

	TType Automat::proofAndState(char input) {
		switch (input) {
			case '&':
				this->state = AND_AND_STATE;
				return CONTINUE;
			default:
				this->state = START_STATE;
				return ERROR;
		}
	}

	TType Automat::proofAndAndState(char input) {
		this->state = START_STATE;
		return SIGN_AND;
	}
