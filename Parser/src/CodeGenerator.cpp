#include <iostream>

#include "../includes/CodeGenerator.h"

using namespace std;

CodeGenerator::CodeGenerator(char* outFile) {
	this->outFile = outFile;
}

CodeGenerator::~CodeGenerator() {
	delete outFile;
}

void CodeGenerator::makeCode(Node* rootNode) {

}
