#include <iostream>

#include "../includes/Node.h"

using namespace std;

Node::Node(TType tType, RuleType ruleType) {
	this->tType = tType;
	this->ruleType = ruleType;
}

Node::~Node() {

}

void Node::addChild(Node* child) {
	children[childrenCounter++] = child;
}

RuleType Node::getRuleType() {
	return ruleType;
}
NodeType Node::getNodeType() {
	return nodeType;
}
TType Node::getTType() {
	return tType;
}
Node** Node::getChildren() {
	return this->children;
}
Node* Node::getChildren(int position) {
	return this->children[position];
}

void Node::setRuleType(RuleType ruleType) {
	this->ruleType = ruleType;
}
void Node::setNodeType(NodeType nodeType) {
	this->nodeType = nodeType;
}

char* Node::tTypeToString() {
	switch(this->tType) {
		case ERROR							:	return "Error"; break;
		case INTEGER						:	return "Integer"; break;
		case IDENTIFIER						:	return "Identifier"; break;
		case SIGN_PLUS						:	return "Plus"; break;
		case SIGN_MINUS						:	return "Minus"; break;
		case SIGN_MULTIPLIER				:	return "Multiplier"; break;
		case SIGN_COLON						:	return "Colon"; break;
		case SIGN_GREATER					:	return "Greater"; break;
		case SIGN_SMALLER					:	return "Smaller"; break;
		case SIGN_EQUAL						:	return "Equal"; break;
		case SIGN_AND						:	return "And"; break;
		case SIGN_SEMICOLON					:	return "Semicolon"; break;
		case SIGN_BRACKET_ON				:	return "Bracket-On"; break;
		case SIGN_BRACKET_CLOSE				:	return "Bracket-Close"; break;
		case SIGN_CURLY_BRACKET_ON			:	return "Curly-Bracket-On"; break;
		case SIGN_CURLY_BRACKET_CLOSE		:	return "Curly-Bracket-Close"; break;
		case SIGN_SQUARE_BRACKET_ON			:	return "Square-Bracket-On"; break;
		case SIGN_SQUARE_BRACKET_CLOSE		:	return "Square-Bracket-Close"; break;
		case SIGN_SPECIAL					:	return "Special =:="; break;
		case SIGN_COLON_EQUAL				:	return "Colon-Equal"; break;
		case SIGN_EXCLEMATION				:	return "Exclamation"; break;
		case COMMENT						:	return "Comment"; break;
		case TOKEN_IF						:	return "If"; break;
		case TOKEN_WHILE					:	return "While"; break;
		case TOKEN_SPACE					:	return "Space"; break;
		case IGNORE							:	return "Ignore"; break;
		case CONTINUE						:	return "Continue"; break;
		case ERROR_SPECIAL					:	return "Error-Special"; break;
		case LINE_BREAK						:	return "Line-Break"; break;
		case END_OF_FILE					:	return "End-of-File"; break;

		//Parser
		case TOKEN_INT						:	return "int"; break;
		case TOKEN_WRITE					:	return "write"; break;
		case TOKEN_READ						:	return "read"; break;
		case TOKEN_ELSE						:	return "else"; break;
	}
	return "";
}
char* Node::ruleTypeToString() {
	switch(this->ruleType) {
		case NO_RULE:
			return "NO_RULE";
			break;
		case PROG:
			return "PROG";
			break;
		case DECLS:
			return "DECLS";
			break;
		case DECL:
			return "DECL";
			break;
		case ARRAY:
			return "ARRAY";
			break;
		case STATEMENTS:
			return "STATEMENTS";
			break;
		case STATEMENT:
			return "STATEMENT";
			break;
		case EXP:
			return "EXP";
			break;
		case EXP2:
			return "EXP2";
			break;
		case INDEX:
			return "INDEX";
			break;
		case OP_EXP:
			return "OP_EXP";
			break;
		case OP:
			return "OP";
			break;
		case EPSIOLN:
			return "EPSILON";
			break;
		case ERROR_RULE:
			return "ERROR_RULE";
			break;
	}
	return "";
}
