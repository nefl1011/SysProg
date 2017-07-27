#ifndef SCANNER_H_
#define SCANNER_H_

#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include "../../Automat/includes/Token.h"

class Scanner {
private:
	Buffer* buffer;
	Automat* automat;
	char currChar;
	int lexemLength;
	char* lexem;
	bool tokenFound;
	int lexemStartCol;
	int col;
	int line;
	TType prevTType;
	TType currTType;

public:
	Scanner(Buffer* buffer, Automat* automat);
	virtual ~Scanner();

	Token* nextToken();
	bool hasNextToken();
};

#endif /* SCANNER_H_ */
