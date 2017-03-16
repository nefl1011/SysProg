/*
 * Scanner.h
 *
 *  Created on: 24.04.2015
 *      Author: nefl1011
 */

#ifndef SCANNER_H_
#define SCANNER_H_
#include <cstring>
#include <iostream>
#include "../../Automat/includes/Automat.h"
#include "../../Buffer/includes/Buffer.h"
#include "TTypes.h"
using namespace std;

class Scanner {
private:
	char* path;
	Automat* automat;
	Buffer* buffer;
	TType typeScanner = automat->currentState();
	char current;
	char* lexemS;
	int lexemLength;
	int lineS;
	int columnS;

public:

	Scanner(char* path);
	~Scanner();

	Token* nextToken();
	int hasNext();

};

#endif /* SCANNER_H_ */
