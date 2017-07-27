/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Scanner.h"
#include "../../Automat/includes/Automat.h"
#include "../../Automat/includes/Token.h"

Scanner::Scanner(Buffer* buffer, Automat* automat) {
	this->buffer = buffer;
	this->automat = automat;

	this->tokenFound = false;
	this->lexemStartCol = 0;
	this->col = 0;
	this->line = 0;
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
}

Token* Scanner::nextToken() {
	while(!tokenFound) {
		if(buffer->hasNext()) {
			currChar = buffer->getChar();
		}

		lexem[col-lexemStartCol] = currChar;

		currTType = automat->proofInput(currChar);

		switch(currTType) {
			case CONTINUE:
			case IGNORE:
				col++;
				continue;

			case LINE_BREAK:
				line++;
				col = 0;
				lexemStartCol = 0;
				continue;

			case ERROR:
				cout << "Error: Das Zeichen \'" << currChar << "\' wird nicht akzeptiert!" << endl;
				abort();
		}

		//Token gefunden
		tokenFound = true;
		buffer->ungetChar();
		lexem[col-lexemStartCol] = '\0';

		//Token zusammenbauen
		/*Token* token = new Token(currTType, lex, line, lexemStartCol);

		cout << "Token " << token->getTypeName() << " Line: " << token->getLine()
				<< " Spalte: " << token->getColumn() << " Lexem: " << token->getLexem() << endl;*/

		cout << "Token " << currTType << " Line: " << line
						<< " Spalte: " << lexemStartCol << " Lexem: " << lexem << endl;

		for(int i = 0; i < (col-lexemStartCol); i++) {
			lexem[i] = '\0';
		}
		lexemStartCol = col;
	}
	tokenFound = false;
}

bool Scanner::hasNextToken() {
	return buffer->hasNext();
}
