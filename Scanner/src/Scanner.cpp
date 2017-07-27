#include "../includes/Scanner.h"
#include "../../Automat/includes/Automat.h"
#include "../../Automat/includes/Token.h"

Scanner::Scanner(char* filePath) {
	this->buffer = new Buffer(filePath);
	this->automat = new Automat();

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
		else {
			col++;
		}

		lexem[col-lexemStartCol] = '\0';

		//bilde seperaten String für Token
		char* string = new char[col-lexemStartCol+1];
		for (int index = 0; index < (col-lexemStartCol)+1; index++) {
			string[index] = lexem[index];
		}

		if (currTType == IDENTIFIER) {
			if (strcmp(string, "IF") == 0 || strcmp(string, "if") == 0) {
				currTType = TOKEN_IF;
			}
			else if (strcmp(string, "WHILE") == 0 || strcmp(string, "while") == 0) {
				currTType = TOKEN_WHILE;
			}
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
