#ifndef CODEGENERATOR_H_
#define CODEGENERATOR_H_

#include "../includes/Node.h"

class CodeGenerator {
private:
	char* outFile;

public:
	CodeGenerator(char* outFile);
	~CodeGenerator();

	void makeCode(Node* rootNode);
};

#endif /* CODEGENERATOR_H_ */
