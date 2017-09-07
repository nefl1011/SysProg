#include <iostream>

#include "../includes/CodeGenerator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

CodeGenerator::CodeGenerator(char* outFile) {
	codeFile = new ofstream(outFile);
	outText = new stringstream();
	labelCounter = 0;
}

CodeGenerator::~CodeGenerator() {
	codeFile->close();
	delete codeFile;
	delete outText;
}

void CodeGenerator::makeCode(Node* rootNode) {
	generateCodeProg(rootNode);
	*codeFile << outText->rdbuf();
	codeFile->flush();
	outText->str(string());
}
void CodeGenerator::generateCode(Node* node) {
	if (node == 0L) {
		return;
	}

	cout << "generate: " << node->ruleTypeToString() << endl;
	switch (node->getRuleType()) {
	case PROG:
		generateCodeProg(node);
		break;
	case DECLS:
		generateCodeDecls(node);
		break;
	case EPSILON:
		generateCodeEmpty();
		break;
	case DECL:
		generateCodeDecl(node);
		break;
	case ARRAY:
		generateCodeArray(node);
		break;
	case STATEMENTS:
		generateCodeStatements(node);
		break;
	case STATEMENT:
		generateCodeStatement(node);
		break;
	case EXP:
		generateCodeExp(node);
		break;
	case EXP2:
		generateCodeExp2(node);
		break;
	case INDEX:
		generateCodeIndex(node);
		break;
	case OP_EXP:
		generateCodeOp_Exp(node);
		break;
	case OP:
		generateCodeOp(node);
		break;
	case LEAF:
		break;
	default:
		cerr << "node is empty" << endl;
	}
}
//PROG ::= DECLS STATEMENTS
void CodeGenerator::generateCodeEmpty() {

}

//PROG ::= DECLS STATEMENTS
void CodeGenerator::generateCodeProg(Node *root) {
	Node* decls = root->getChildren(0);
	Node* statements = root->getChildren(1);

	generateCode(decls);
	generateCode(statements);

	*outText << "STP";
}

//DECLS ::= DECL ; DECLS
void CodeGenerator::generateCodeDecls(Node* node) {
	Node* decl = node->getChildren(0);
	Node* decls = node->getChildren(1);

	generateCode(decl);
	generateCode(decls);
}

//DECL::= int ARRAY identifier
void CodeGenerator::generateCodeDecl(Node *node) {
	Node* array = node->getChildren(0);
	Node* identifier = node->getChildren(1);
	if (identifier != 0L) {
		*outText << " DS " << "$" << identifier->getToken()->getLexem();
	}

	generateCodeArray(array);
}

//ARRAY::=[integer]
void CodeGenerator::generateCodeArray(Node* node) {
	if (node == 0L) {
		return;
	}

	cout << "generate: " << node->ruleTypeToString() << endl;

	if (node->getRuleType() == EPSILON) {
		*outText << " " << 1;
	}
	else {
		Node* array = node->getChildren(0);
		if (array != 0L) {
			*outText << " " << array->getToken()->getValue();
		}
	}
}

//STATEMENTS ::= STATEMENT_IDENTIFIER ; STATEMENTS)
void CodeGenerator::generateCodeStatements(Node *node) {
	Node* statement = node->getChildren(0);
	Node* statements = node->getChildren(1);

	generateCode(statement);

	if (statement != 0L) {
		generateCode(statements);
	}
}

void CodeGenerator::generateCodeStatement(Node *node) {
	if (node == 0L) {
		cout << "node is null" << endl;
		return;
	}
	switch (node->getTType()) {
	case IDENTIFIER:
		generateCodeStatement_IDENTIFIER(node);
		break;
	case TOKEN_WRITE:
		generateCodeStatement_WRITE(node);
		break;
	case TOKEN_READ:
		generateCodeStatement_READ(node);
		break;
	case SIGN_CURLY_BRACKET_ON:
		generateCodeStatement_BRACES(node);
		break;
	case TOKEN_IF:
		generateCodeStatement_IF(node);
		break;
	case TOKEN_WHILE:
		generateCodeStatement_WHILE(node);
		break;
	}
}

//STATEMENT_IDENTIFIER ::= identifier INDEX := EXP
void CodeGenerator::generateCodeStatement_IDENTIFIER(Node *node) {
	Node* identifier = node->getChildren(0);
	Node* index = node->getChildren(1);
	Node* exp = node->getChildren(2);

	generateCode(exp);
	if (identifier) {
		*outText << " LA " << "$" << identifier->getToken()->getLexem();
	}

	generateCode(index);
	*outText << " STR ";
}

//STATEMENT_IDENTIFIER ::= write( EXP )
void CodeGenerator::generateCodeStatement_WRITE(Node *node) {
	Node* exp = node->getChildren(0);
	generateCode(exp);

	*outText << " PRI ";
}

//STATEMENT_IDENTIFIER ::= read( identifier INDEX)
void CodeGenerator::generateCodeStatement_READ(Node *node) {
	Node* identifier = node->getChildren(0);
	Node* index = node->getChildren(1);

	*outText << " REA ";
	if (identifier) {
		*outText << " LA " << "$" << identifier->getToken()->getLexem();
	}

	generateCode(index);

	*outText << " STR ";
}

//STATEMENT_IDENTIFIER ::= { STATEMENTS }
void CodeGenerator::generateCodeStatement_BRACES(Node *node) {
	Node* statements = node->getChildren(0);
	generateCode(statements);
}

//STATEMENT_IDENTIFIER ::= if ( EXP ) STATEMENT_IDENTIFIER else STATEMENT_IDENTIFIER
void CodeGenerator::generateCodeStatement_IF(Node *node) {
	Node* exp = node->getChildren(0);
	Node* statement1 = node->getChildren(1);
	Node* statement2 = node->getChildren(2);
	int label1 = ++labelCounter;
	int label2 = ++labelCounter;

	generateCode(exp);

	*outText << " JIN " << "#label" << label1 << " ";

	generateCode(statement1);

	*outText << " JMP " << "#label" << label2 << " ";
	*outText << "#label" << label1 << " NOP ";

	generateCode(statement2);

	*outText << "#label" << label2 << " NOP ";
}

//STATEMENT_IDENTIFIER ::= while ( EXP ) STATEMENT_IDENTIFIER)
void CodeGenerator::generateCodeStatement_WHILE(Node *node) {
	Node* exp = node->getChildren(0);
	Node* statement = node->getChildren(1);

	int label1 = ++labelCounter;
	int label2 = ++labelCounter;

	*outText << "#label" << label1 << " NOP ";

	generateCode(exp);

	*outText << " JIN " << "#label" << label2 << " ";

	generateCode(statement);

	*outText << " JMP " << "#label" << label1 << " ";
	*outText << "#label" << label2 << " NOP ";
}

//EXP ::= EXP2_PARENS OP_EXP
void CodeGenerator::generateCodeExp(Node* node) {
	Node* exp2 = node->getChildren(0);
	Node* op_exp = node->getChildren(1);

	if (op_exp != 0L) {
		if (op_exp->getNodeType() == NO_TYPE) {
			generateCode(exp2);
		}
		else if (op_exp->getChildren(0)->getNodeType() == OP_GREATER_TYPE) {
			generateCode(op_exp);
			generateCode(exp2);
			*outText << " LES ";
		} else if (op_exp->getChildren(0)->getNodeType() == OP_SPECIAL_TYPE) {
			generateCode(exp2);
			generateCode(op_exp);
			*outText << " NOT ";
		} else {
			generateCode(exp2);
			generateCode(op_exp);
		}

	}
}

void CodeGenerator::generateCodeExp2(Node* node) {
	if (node == 0L) {
		cout << "node is null" << endl;
		return;
	}
	switch (node->getTType()) {
	case SIGN_BRACKET_ON:
		generateCodeExp2_SIGN_BRACKET_ON(node);
		break;
	case IDENTIFIER:
		generateCodeExp2_IDENTIFIER(node);
		break;
	case INTEGER:
		generateCodeExp2_INTEGER(node);
		break;
	case SIGN_MINUS:
		generateCodeExp2_MINUS(node);
		break;
	case SIGN_EXCLEMATION:
		generateCodeExp2_EXCLEMATION(node);
		break;
	}
}

//INDEX ::= [ EXP ]
void CodeGenerator::generateCodeExp2_SIGN_BRACKET_ON(Node *node) {
	Node* exp = node->getChildren(0);
	generateCode(exp);
}

//EXP2_PARENS ::= identifier INDEX
void CodeGenerator::generateCodeExp2_IDENTIFIER(Node *node) {
	Node* index = node->getChildren(0);
	Node* identifier = node->getChildren(1);

	if (identifier) {
		*outText << " LA " << "$" << identifier->getToken()->getLexem();
	}

	generateCode(index);

	*outText << " LV ";
}

//EXP2_PARENS ::= integer
void CodeGenerator::generateCodeExp2_INTEGER(Node *node) {
	if (node->getChildren(0)) {
		*outText << " LC " << node->getChildren(0)->getToken()->getValue();
	}
}

//EXP2_PARENS ::= - EXP2_PARENS
void CodeGenerator::generateCodeExp2_EXCLEMATION(Node *node) {
	Node *exp2 = node->getChildren(0);

	*outText << "LC " << 0;
	generateCode(exp2);
	*outText << " SUB ";
}

//EXP2_PARENS ::= ! EXP2_PARENS
void CodeGenerator::generateCodeExp2_MINUS(Node *node) {
	Node* exp2 = node->getChildren(0);

	generateCode(exp2);
	*outText << " NOT ";
}

//INDEX ::= [ EXP ]
void CodeGenerator::generateCodeIndex(Node* node) {
	Node* exp = node->getChildren(0);

	generateCode(exp);
	*outText << " ADD ";
}

//INDEX ::= e
void CodeGenerator::generateCodeIndex_EMPTY() {
}

//OP_EXP ::= OP_PLUS EXP
void CodeGenerator::generateCodeOp_Exp(Node* node) {
	Node* op = node->getChildren(0);
	Node* exp = node->getChildren(1);

	generateCode(exp);
	generateCode(op);
}
void CodeGenerator::generateCodeOp(Node* node) {
	if (node == 0L) {
		cout << "node is null" << endl;
		return;
	}
	switch (node->getTType()) {
	case SIGN_PLUS:
		generateCodeOp_PLUS();
		break;
	case SIGN_MINUS:
		generateCodeOp_MINUS();
		break;
	case SIGN_MULTIPLIER:
		generateCodeOp_MULTIPLIER();
		break;
	case SIGN_COLON:
		generateCodeOp_COLON();
		break;
	case SIGN_SMALLER:
		generateCodeOp_SMALLER();
		break;
	case SIGN_GREATER:
		generateCodeOp_GREATER();
		break;
	case SIGN_EQUAL:
		generateCodeOp_EQUAL();
		break;
	case SIGN_AND:
		generateCodeOp_AND();
		break;
	case SIGN_SPECIAL:
		generateCodeOp_SPECIAL();
		break;
	}
}

void CodeGenerator::generateCodeOp_PLUS() {
	*outText << " ADD ";
}

void CodeGenerator::generateCodeOp_MINUS() {
	*outText << " SUB ";
}

void CodeGenerator::generateCodeOp_MULTIPLIER() {
	*outText << " MUL ";
}

void CodeGenerator::generateCodeOp_COLON() {
	*outText << " DIV ";
}

void CodeGenerator::generateCodeOp_SMALLER() {
	*outText << " LES ";
}

void CodeGenerator::generateCodeOp_GREATER() {
	*outText << "  ";
}

void CodeGenerator::generateCodeOp_EQUAL() {
	*outText << " EQU ";

}

void CodeGenerator::generateCodeOp_SPECIAL() {
	*outText << " EQU ";
}

void CodeGenerator::generateCodeOp_AND() {
	*outText << " AND ";
}

