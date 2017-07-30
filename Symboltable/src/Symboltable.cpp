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
	hashmapPtr->insertToken(new Token(TOKEN_IF, "if", 0, 0));
	hashmapPtr->insertToken(new Token(TOKEN_IF, "IF", 0, 0));

	hashmapPtr->insertToken(new Token(TOKEN_WHILE, "while", 0, 0));
	hashmapPtr->insertToken(new Token(TOKEN_WHILE, "WHILE", 0, 0));
}

TType Symboltable::getTokenType(char* lexem) {
	return this->hashmapPtr->getTokenType(lexem);
}

bool Symboltable::insertToken(Token* t) {
	return this->hashmapPtr->insertToken(t);
}


