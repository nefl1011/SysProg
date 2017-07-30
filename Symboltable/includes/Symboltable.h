/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "HashMap.h"

class Symboltable {
public:
	HashMap* hashmapPtr;

	Symboltable();
	virtual ~Symboltable();

	void initSymbols();

	bool insertToken(Token* t);

	TType getTokenType(char* lexem);

};

#endif /* SYMBOLTABLE_H_ */
