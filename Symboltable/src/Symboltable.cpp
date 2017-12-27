/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Symboltable.h"

Symboltable::Symboltable() {
	this->hashmapPtr = new HashMap(1000);
	this->initSymbols();

}

Symboltable::~Symboltable() {
	delete hashmapPtr;
}

void Symboltable::initSymbols() {
	Token* tokenIf = new Token(TOKEN_IF, "if", 0, 0);
	Token* tokenIF = new Token(TOKEN_IF, "IF", 0, 0);
	Token* tokenWhile = new Token(TOKEN_WHILE, "while", 0, 0);
	Token* tokenWHILE = new Token(TOKEN_WHILE, "WHILE", 0, 0);
	Token* tokenInt = new Token(TOKEN_INT, "int", 0, 0);
	Token* tokenWrite = new Token(TOKEN_WRITE, "write", 0, 0);
	Token* tokenRead = new Token(TOKEN_READ, "read", 0, 0);
	Token* tokenElse = new Token(TOKEN_ELSE, "else", 0, 0);

	hashmapPtr->insertToken(tokenIf);
	hashmapPtr->insertToken(tokenIF);

	hashmapPtr->insertToken(tokenWhile);
	hashmapPtr->insertToken(tokenWHILE);

	hashmapPtr->insertToken(tokenInt);
	hashmapPtr->insertToken(tokenRead);
	hashmapPtr->insertToken(tokenWrite);
	hashmapPtr->insertToken(tokenElse);
}

TType Symboltable::getTokenType(char* lexem) {
	return this->hashmapPtr->getTokenType(lexem);
}

Token* Symboltable::getToken(char* lexem) {
	return this->hashmapPtr->getToken(lexem);
}

Token* Symboltable::insertToken(Token* t) {
	return this->hashmapPtr->insertToken(t);
}


