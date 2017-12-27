#include "../includes/Scanner.h"
#include "../../Automat/includes/Automat.h"
#include "../../Automat/includes/Token.h"

Scanner::Scanner(char* filePath) {
	this->buffer = new Buffer(filePath);
	this->automat = new Automat();
	this->symboltable = new Symboltable();

	this->tokenFound = false;
	this->lexemStartCol = 0;
	this->col = 0;
	this->line = 0;
	this->lexemLength = 256;
	this->lexem = new char[this->lexemLength];
	this->currChar = '\0';
	this->currTType = ERROR;
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete symboltable;
	delete lexem;
}

Token* Scanner::nextToken() {
	Token* token;
	while(!tokenFound) {
		if (buffer->hasNext()) {
			currChar = buffer->getChar();
		}
		else {
			currChar = '\0';
		}

		currTType = automat->proofInput(currChar);

		switch(currTType) {
			case CONTINUE:
				if (col-lexemStartCol < this->lexemLength) {
					lexem[col-lexemStartCol] = currChar;
				}
			case IGNORE:
				col++;
				if (currChar == '\n') {
					line++;
					col = 0;
				} else if(currChar == '\0') {
					currTType = END_OF_FILE;
					break;
				}
				continue;

			case TOKEN_SPACE:
			case COMMENT:
				if(currChar != '\0'){
					buffer->ungetChar();
				}
				lexemStartCol = col;
				continue;

			case LINE_BREAK:
				line++;
				col = 0;
				lexemStartCol = 0;
				continue;

			case ERROR:
				lexem[col-lexemStartCol] = currChar;
				break;

			case ERROR_SPECIAL:
				col--;
				buffer->ungetChar();
				currTType = SIGN_EQUAL;
				break;

			case ERROR_AND:
				col--;
				if(currChar != '\0') {
					buffer->ungetChar();
				}
				currTType = ERROR;
				break;
		}

		//Token gefunden
		tokenFound = true;

		if (currTType != ERROR && currChar != '\0') {
			buffer->ungetChar();
		}
		else {
			col++;
		}

		//bilde seperaten String für Token
		int stringLength = col - lexemStartCol + 1;
		char* string;

		//überprüfe die Länge des zu bildenden strings
		if (stringLength > this->lexemLength) {
			if (currTType == IDENTIFIER) {
				string = "Identifier too long";
			}
			else if (currTType == INTEGER) {
				string = "Integer out of range";
			}
			else {
				string = "Lexem too long";
			}
			currTType = ERROR;
		}
		else {
			string = new char[col-lexemStartCol + 1];
			for (int index = 0; index < (col-lexemStartCol) + 1; index++) {
				if (index == col-lexemStartCol) {
					string[index] = '\0';
				}
				else {
					string[index] = lexem[index];
				}
			}
		}

		//überprüfe nach Schlüsselwörtern
		if (currTType == IDENTIFIER) {
			if (strcmp(string, "IF") == 0 || strcmp(string, "if") == 0) {
				currTType = TOKEN_IF;
			}
			else if (strcmp(string, "WHILE") == 0 || strcmp(string, "while") == 0) {
				currTType = TOKEN_WHILE;
			}

			//Parser
			else if (strcmp(string, "int") == 0) {
				currTType = TOKEN_INT;
			}
			else if (strcmp(string, "write") == 0) {
				currTType = TOKEN_WRITE;
			}
			else if (strcmp(string, "read") == 0) {
				currTType = TOKEN_READ;
			}
			else if (strcmp(string, "else") == 0) {
				currTType = TOKEN_ELSE;
			}
		}

		//bilde Token
		token = new Token(currTType, string, line, lexemStartCol);
		if(currTType == IDENTIFIER) {
			token = symboltable->insertToken(token);
		}

		//resete lexem
		int resetIndex = col-lexemStartCol > this->lexemLength ? this->lexemLength : col-lexemStartCol;
		for(int i = 0; i < resetIndex; i++) {
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

Symboltable* Scanner::getSymboltable() {
	return this->symboltable;
}
