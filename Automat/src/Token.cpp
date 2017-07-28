#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "../includes/Token.h"

using namespace std;

Token::Token(TType type, char* lexem, int line, int column) {
	this->type = type;
	this->lexem = lexem;
	this->line = line;
	this->column = column;

	if (this->type != INTEGER) {
		this->value = -1;
	}
	else {
		this->value = strtol(this->lexem, NULL, 0);
		if (this->value == -1) {
			this->lexem = "Integer out of range";
			this->type = ERROR;
		}
	}

	switch(type) {
		case ERROR							:	this->typeName = "Error"; break;
		case INTEGER						:	this->typeName = "Integer"; break;
		case IDENTIFIER						:	this->typeName = "Identifier"; break;
		case SIGN_PLUS						:	this->typeName = "Plus"; break;
		case SIGN_MINUS						:	this->typeName = "Minus"; break;
		case SIGN_MULTIPLIER				:	this->typeName = "Multiplier"; break;
		case SIGN_COLON						:	this->typeName = "Colon"; break;
		case SIGN_GREATER					:	this->typeName = "Greater"; break;
		case SIGN_SMALLER					:	this->typeName = "Smaller"; break;
		case SIGN_EQUAL						:	this->typeName = "Equal"; break;
		case SIGN_AND						:	this->typeName = "And"; break;
		case SIGN_SEMICOLON					:	this->typeName = "Semicolon"; break;
		case SIGN_BRACKET_ON				:	this->typeName = "Bracket-On"; break;
		case SIGN_BRACKET_CLOSE				:	this->typeName = "Bracket-Close"; break;
		case SIGN_CURLY_BRACKET_ON			:	this->typeName = "Curly-Bracket-On"; break;
		case SIGN_CURLY_BRACKET_CLOSE		:	this->typeName = "Curly-Bracket-Close"; break;
		case SIGN_SQUARE_BRACKET_ON			:	this->typeName = "Square-Bracket-On"; break;
		case SIGN_SQUARE_BRACKET_CLOSE		:	this->typeName = "Square-Bracket-Close"; break;
		case SIGN_SPECIAL					:	this->typeName = "Special"; break;
		case SIGN_COLON_EQUAL				:	this->typeName = "Colon-Equal"; break;
		case SIGN_EXCLEMATION				:	this->typeName = "Exclamation"; break;
		case COMMENT						:	this->typeName = "Comment"; break;
		case TOKEN_IF						:	this->typeName = "If"; break;
		case TOKEN_WHILE					:	this->typeName = "While"; break;
		case TOKEN_SPACE					:	this->typeName = "Space"; break;
		case IGNORE							:	this->typeName = "Ignore"; break;
		case CONTINUE						:	this->typeName = "Continue"; break;
		case ERROR_SPECIAL					:	this->typeName = "Error-Special"; break;
		case LINE_BREAK						:	this->typeName = "Line-Break"; break;
		case END_OF_FILE					:	this->typeName = "End-of-File"; break;
	}
}

Token::~Token() {
	delete this->lexem;
	delete this->typeName;
}

TType Token::getType() {
	return this->type;
}

char* Token::getTypeName() {
	return this->typeName;
}

char* Token::getLexem() {
	return this->lexem;
}

int Token::getLine() {
	return this->line;
}

int Token::getColumn() {
	return this->column;
}

int Token::getValue() {
	return this->value;
}


