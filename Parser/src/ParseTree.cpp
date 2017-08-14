#include <iostream>

#include "../includes/ParseTree.h"

using namespace std;

ParseTree::ParseTree(char* inFile, char* outFile) {
	scanner = new Scanner(inFile);
	parser = new Parser(scanner);
	typeChecker = new TypeChecker();
	codeGenerator = new CodeGenerator(outFile);
}

ParseTree::~ParseTree() {
	delete scanner;
	delete parser;
	delete typeChecker;
	delete codeGenerator;
	delete rootNode;
}

void ParseTree::parse() {
	this->rootNode = parser->parse();
}

void ParseTree::typeCheck() {
	this->rootNode = typeChecker->typeCheck(rootNode);
}

void ParseTree::makeCode() {
	codeGenerator->makeCode(this->rootNode);
}

Node* ParseTree::getRootNode() {
	return this->rootNode;
}
