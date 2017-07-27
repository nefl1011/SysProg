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
	this->lexemLength = 256;
	this->lexem = new char[this->lexemLength];
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete[] lexem;
}

Token* Scanner::nextToken() {
	Token* token;
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

			case ERROR_SPECIAL:
				col--;
				buffer->ungetChar();
				currTType = SIGN_EQUAL;
				break;

			case ERROR_AND:
				col--;
				buffer->ungetChar();
				currTType = ERROR;
				break;
		}

		//Token gefunden
		tokenFound = true;

		if (currTType != ERROR) {
			buffer->ungetChar();
		}

		lexem[col-lexemStartCol] = '\0';

		//bilde seperaten String für Token
		char* string = new char[col-lexemStartCol];
		for (int index = 0; index < (col-lexemStartCol); index++) {
			string[index] = lexem[index];
		}

		//bilde Token
		token = new Token(currTType, string, line, lexemStartCol);

		//resete lexem
		for(int i = 0; i < (col-lexemStartCol); i++) {
			lexem[i] = '\0';
		}

		lexemStartCol = col;
	}
	tokenFound = false;
	return token;
}

bool Scanner::hasNextToken() {
	return buffer->hasNext();
}
