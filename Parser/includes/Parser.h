#ifndef PARSER_H_
#define PARSER_H_

#include "../../Scanner/includes/Scanner.h"
#include "../includes/Node.h"

class Parser {
private:
	Scanner* scanner;

	Token* currToken;
	void nextToken();

	Node* prog();
	Node* decls();
	Node* statements();
	Node* decl();
	Node* array();
	Node* statement();
	Node* index();
	Node* exp();
	Node* exp2();
	Node* op_exp();
	Node* op();
	Node* epsilon();

	bool first(RuleType ruleType);
	bool checkTType(TType tType);

	void error();

public:
	Parser(Scanner* scanner);
	~Parser();

	Node* parse();
};

#endif /* PARSER_H_ */
