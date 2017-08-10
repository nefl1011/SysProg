#ifndef PARSER_H_
#define PARSER_H_

#include "../../Scanner/includes/Scanner.h"
#include "../includes/Node.h"

class Parser {
private:
	Scanner* scanner;

public:
	Parser(Scanner* scanner);
	~Parser();

	Node* parse();
};

#endif /* PARSER_H_ */
