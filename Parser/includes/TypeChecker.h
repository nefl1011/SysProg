#ifndef TYPECHECKER_H_
#define TYPECHECKER_H_

#include "../includes/Node.h"
#include "../../Symboltable/includes/Symboltable.h"

class TypeChecker {
private:
	char* errorOutFile;
	Symboltable* symboltable;
public:
	TypeChecker(char* errorOutFile, Symboltable* aSymboltable);
	~TypeChecker();

	Node* typeCheck(Node* rootNode);

	void analyze(Node *root);
	Node* typeCheckProg(Node* root);
	void typeCheckDecls(Node* root);
	void typeCheckDecls_EMPTY(Node *root);
	void typeCheckDecl(Node* root);
	void typeCheckEmpty(Node* root);
	void typeCheckArray(Node* root);
	void typeCheckStatements(Node* root);
	void typeCheckStatement(Node *root);
	void typeCheckStatement_IDENTIFIER(Node *root);
	void typeCheckStatement_WRITE(Node *root);
	void typeCheckStatement_READ(Node *root);
	void typeCheckStatement_BRACES(Node *root);
	void typeCheckStatement_IF(Node *root);
	void typeCheckStatement_WHILE(Node *root);
	void typeCheckExp(Node* root);
	void typeCheckExp2(Node* root);
	void typeCheckExp2_SIGN_BRACKET_ON(Node *root);
	void typeCheckExp2_IDENTIFIER(Node *root);
	void typeCheckExp2_INTEGER(Node *root);
	void typeCheckExp2_MINUS(Node *root);
	void typeCheckExp2_EXCLEMATION(Node *root);
	void typeCheckIndex(Node* root);
	void typeCheckOp_Exp(Node* root);
	void typeCheckOp(Node* root);
	void typeCheckOp_PLUS(Node *root);
	void typeCheckOp_MINUS(Node *root);
	void typeCheckOp_MULTIPLIER(Node *root);
	void typeCheckOp_COLON(Node *root);
	void typeCheckOp_SMALLER(Node *root);
	void typeCheckOp_GREATER(Node *root);
	void typeCheckOp_EQUAL(Node *root);
	void typeCheckOp_SPECIAL(Node *root);
	void typeCheckOp_AND(Node *root);
	void error(const char* errorString, Node* node);
	void store(Node* aNode, NodeType aNodeType);
	NodeType getNodeTypeSymTable(Node* aNode);
};

#endif /* TYPECHECKER_H_ */
