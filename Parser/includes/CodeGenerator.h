#ifndef CODEGENERATOR_H_
#define CODEGENERATOR_H_

#include "../includes/Node.h"

class CodeGenerator {

public:
	CodeGenerator(char* outFile);
	~CodeGenerator();

	void makeCode(Node* rootNode);

private:

	std::ofstream* codeFile;
	std::stringstream* outText;

	int labelCounter;

	void generateCode(Node* root);

	void generateCodeProg(Node* root);
	void generateCodeDecls(Node* root);
	void generateCodeEmpty();
	void generateCodeEmptyStatements();
	void generateCodeEmptyArray();
	void generateCodeDecl(Node* root);
	void generateCodeArray(Node* root);
	void generateCodeStatements(Node* root);
	void generateCodeStatement(Node* root);
	void generateCodeStatement_IDENTIFIER(Node *root);
	void generateCodeStatement_WRITE(Node *root);
	void generateCodeStatement_READ(Node *root);
	void generateCodeStatement_BRACES(Node *root);
	void generateCodeStatement_IF(Node *root);
	void generateCodeStatement_WHILE(Node *root);
	void generateCodeExp(Node* root);
	void generateCodeExp2(Node* root);
	void generateCodeExp2_SIGN_BRACKET_ON(Node *root);
	void generateCodeExp2_IDENTIFIER(Node *root);
	void generateCodeExp2_INTEGER(Node *root);
	void generateCodeExp2_MINUS(Node *root);
	void generateCodeExp2_EXCLEMATION(Node *root);
	void generateCodeIndex(Node* root);
	void generateCodeIndex_EMPTY();
	void generateCodeOp_Exp(Node* root);
	void generateCodeOp(Node* root);
	void generateCodeOp_PLUS();
	void generateCodeOp_MINUS();
	void generateCodeOp_MULTIPLIER();
	void generateCodeOp_COLON();
	void generateCodeOp_SMALLER();
	void generateCodeOp_GREATER();
	void generateCodeOp_EQUAL();
	void generateCodeOp_SPECIAL();
	void generateCodeOp_AND();
};


#endif /* CODEGENERATOR_H_ */
