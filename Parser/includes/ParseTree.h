#ifndef PARSETREE_H_
#define PARSETREE_H_

#include "../../Scanner/includes/Scanner.h"
#include "../includes/Parser.h"
#include "../includes/TypeChecker.h"
#include "../includes/CodeGenerator.h"
#include "../includes/Node.h"


class ParseTree {
private:
	Scanner* scanner;
	Parser* parser;
	TypeChecker* typeChecker;
	CodeGenerator* codeGenerator;
	Node* rootNode;

public:
	ParseTree(char* inFile, char* outFile);
	~ParseTree();

	void parse();

	void typeCheck();

	void makeCode();

	Node* getRootNode();
};

#endif /* PARSETREE_H_ */
