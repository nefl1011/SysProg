#ifndef SCANNER_H_
#define SCANNER_H_

#include "../../Buffer/includes/Buffer.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Automat/includes/Automat.h"
#include "../../Automat/includes/Token.h"

class Scanner {
private:
	Buffer* buffer;
	Automat* automat;
	Symboltable* symboltable;

	char currChar;
	int lexemLength;
	char* lexem;
	bool tokenFound;
	int lexemStartCol;
	int col;
	int line;
	TType currTType;

public:
	Scanner(char* filePath);
	virtual ~Scanner();

	Token* nextToken();
	bool hasNextToken();
};

#endif /* SCANNER_H_ */
