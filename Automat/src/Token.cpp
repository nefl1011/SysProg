/*
 * Token.cpp
 *
 *  Created on: 24.04.2015
 *      Author: nefl1011
 */
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
	this->value = strtol(this->lexem, NULL, 0);
}

Token::~Token() {
	delete[] this->lexem;
}

TType Token::getType() {
	return this->type;
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


