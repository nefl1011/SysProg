#include <iostream>
#include <fstream>

#include "../includes/ParseTree.h"

using namespace std;

ParseTree::ParseTree(char* inFile, char* outFile) {
	scanner = new Scanner(inFile);
	parser = new Parser(scanner);
	typeChecker = new TypeChecker();
	codeGenerator = new CodeGenerator(outFile);

	char* errorOutFile = (char*) "Parser-error.txt";
	clearErrorOutFile(errorOutFile);
	ofstream errStream(errorOutFile, std::ios_base::app);
	errStream << "parsing ..." << endl;
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

void ParseTree::clearErrorOutFile(const char *errorOutFile) {
    ofstream ofs;
    ofs.open(errorOutFile, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.is_open()) {
        cerr << "Error! Cannot write to output file <" << errorOutFile << ">" << endl;
        exit(EXIT_FAILURE);
    }
    ofs.close();
}
