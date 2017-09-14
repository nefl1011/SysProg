#ifndef PARSER_H_
#define PARSER_H_

#include "../../Scanner/includes/Scanner.h"
#include "../includes/Node.h"

class Parser {
private:
	Scanner* scanner;
	char* errorOutFile;

	Token* currToken;
	void nextToken();
	TType expectedTType;

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
	Node* epsilon(RuleType epsilonRuleType);

	Node* createLeaf();

	bool first(RuleType ruleType);
	bool checkTType(TType tType);

	void error();
	char* tTypeToString(TType tType);

public:
	Parser(Scanner* scanner, char* errorOutFile);
	~Parser();

	Node* parse();
};

#endif /* PARSER_H_ */
