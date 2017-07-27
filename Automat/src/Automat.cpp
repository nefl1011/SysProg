/*
 * Automat.cpp
 *
 *  Created on: 23.04.2015
 *      Author: nefl1011
 */

#include <iostream>

using namespace std;

#include "../includes/Automat.h"

#include "../includes/Token.h"

	Automat::Automat() {
		this->state = States::START_STATE;
		this->sign = '\0';
	}

	Automat::~Automat() {
	}

	TType Automat::proofInput(char input) {
		switch (this->state) {
			case States::START_STATE			: return proofStartState(input);
			case States::IDENTIFIER_STATE		: return proofIdentifierState(input);
			case States::INT_STATE				: return proofIntState(input);
			case States::SIGN_STATE				: return proofSignState();
			case States::EQUAL_STATE			: return proofEqualState(input);
			case States::COLON_STATE			: return proofColonState(input);
			case States::COMMENT_STATE			: return proofCommentState(input);
			case States::COMMENT_END_BEGIN_STATE: return proofCommentEndBeginState(input);
			case States::COMMENT_END_STATE		: return proofCommentEndState(input);
			case States::EQUAL_COLON_STATE		: return proofEqualColonState(input);
			case States::SPECIAL_STATE			: return proofSpecialState(input);
			case States::COLON_EQUAL_STATE	 	: return proofColonEqualState(input);
			case States::SPACE_STATE 			: return proofSpaceState(input);
			case States::AND_STATE			 	: return proofColonEqualState(input);
			case States::AND_AND_STATE 			: return proofSpaceState(input);
			default: return TType::ERROR;
		}
	}

	TType Automat::proofStartState(char input) {
		if ((input >= 'a' && input <= 'z')
			|| (input >= 'A' && input <= 'Z')) {
			this->state = States::IDENTIFIER_STATE;
			return TType::CONTINUE;
		}
		if (input >= '0' && input <= '9') {
			this->state = States::INT_STATE;
			return TType::CONTINUE;
		}

		switch (input) {
			case '=':
				this->state = States::EQUAL_STATE;
				return TType::CONTINUE;
			case ':':
				this->state = States::COLON_STATE;
				return TType::CONTINUE;
			case '&':
				this->state = States::AND_STATE;
				return TType::CONTINUE;
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
				this->state = States::SIGN_STATE;
				return TType::CONTINUE;
			case ' ':
			/*********/
			case '\t':
			case '\b':
			case '\r':
			case '\f':
			/*********/
				this->state = States::SPACE_STATE;
				return TType::IGNORE;
		}

		if(input == '\n') {
			this->state = States::START_STATE;
			return TType::LINE_BREAK;
		}

		return TType::ERROR;
	}

	TType Automat::proofIdentifierState(char input) {
		if ((input >= 'a' && input <= 'z')
			|| (input >= 'A' && input <= 'Z')
			|| (input >= '0' && input <= '9')) {
			return TType::CONTINUE;
		}
		this->state = States::START_STATE;
		return TType::IDENTIFIER;
	}

	TType Automat::proofIntState(char input) {
		if (input >= '0' && input <= '9') {
			return TType::CONTINUE;
		}
		this->state = States::START_STATE;
		return TType::INTEGER;
	}

	TType Automat::proofSignState() {
		this->state = States::START_STATE;
		switch (this->sign) {
			case '+':
				return TType::SIGN_PLUS;
			case '-':
				return TType::SIGN_MINUS;
			case '*':
				return TType::SIGN_MULTIPLIER;
			case '<':
				return TType::SIGN_SMALLER;
			case '>':
				return TType::SIGN_GREATER;
			case '!':
				return TType::SIGN_EXCLEMATION;
			case ';':
				return TType::SIGN_SEMICOLON;
			case '(':
				return TType::SIGN_BRACKET_ON;
			case ')':
				return TType::SIGN_BRACKET_CLOSE;
			case '{':
				return TType::SIGN_CURLY_BRACKET_ON;
			case '}':
				return TType::SIGN_CURLY_BRACKET_CLOSE;
			case '[':
				return TType::SIGN_SQUARE_BRACKET_ON;
			case ']':
				return TType::SIGN_SQUARE_BRACKET_CLOSE;
		}
	}

	TType Automat::proofEqualState(char input) {
		switch (input) {
			case ':':
				this->state = States::EQUAL_COLON_STATE;
				return TType::CONTINUE;
			default:
				return TType::SIGN_EQUAL;
		}
	}

	TType Automat::proofColonState(char input) {
		switch (input) {
			case '*':
				this->state = States::COMMENT_STATE;
				return TType::IGNORE;
			case '=':
				this->state = States::COLON_EQUAL_STATE;
				return TType::CONTINUE;
			default:
				this->state = States::START_STATE;
				return TType::SIGN_COLON;
		}
	}

	TType Automat::proofCommentState(char input) {
		switch (input) {
			case '*':
				this->state = States::COMMENT_END_BEGIN_STATE;
				return TType::CONTINUE;
			default:
				return TType::IGNORE;
		}
	}

	TType Automat::proofCommentEndBeginState(char input) {
		switch (input) {
			case ':':
				this->state = States::COMMENT_END_STATE;
				return TType::CONTINUE;
			default:
				this->state = States::COMMENT_STATE;
				return TType::IGNORE;
		}
	}

	TType Automat::proofCommentEndState(char input) {
		this->state = States::START_STATE;
		return TType::COMMENT;
	}

	TType Automat::proofEqualColonState(char input) {
		switch (input) {
			case '=':
				this->state = States::SPECIAL_STATE;
				return TType::CONTINUE;
			default:
				return TType::ERROR_SPECIAL;
		}
	}

	TType Automat::proofSpecialState(char input) {
		this->state = States::START_STATE;
		return TType::SIGN_SPECIAL;
	}

	TType Automat::proofColonEqualState(char input) {
		this->state = States::START_STATE;
		return TType::SIGN_COLON_EQUAL;
	}

	TType Automat::proofSpaceState(char input) {
		switch (input) {
			case ' ':
				return TType::IGNORE;
			default:
				this->state = States::START_STATE;
				return TType::TOKEN_SPACE;
		}
	}

	TType Automat::proofAndState(char input) {
		switch (input) {
			case '&':
				this->state = States::AND_AND_STATE;
				return TType::CONTINUE;
			default:
				this->state = States::START_STATE;
				return TType::ERROR;
		}
	}

	TType Automat::proofAndAndState(char input) {
		this->state = States::START_STATE;
		return TType::SIGN_AND;
	}
