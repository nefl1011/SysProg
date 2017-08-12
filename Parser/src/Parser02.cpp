#include <iostream>

#include "../includes/Parser.h"

using namespace std;

Parser::Parser(Scanner* scanner) {
	this->scanner = scanner;
}

Parser::~Parser() {
	delete scanner;
}

Node* Parser::parse() {
	return this->prog();
}

Node* Parser::prog() {
	nextToken();
	Node* node = new Node(currToken->getType(), PROG);
	node->addChild(decls());
	node->addChild(statements());
	return node;
}
Node* Parser::decls() {
	Node* node = new Node(currToken->getType(), DECLS);
	node->addChild(decl());
	if(node->getNodeType() != ERROR_RULE) {
		nextToken();
		if(checkTType(SIGN_SEMICOLON)) {
			node->addChild(decls());
			return node;
		}
	} else {
		node->setRuleType(EPSIOLN);
		return node;
	}
}
Node* Parser::decl() {
	Node* node = new Node(currToken->getType(), DECL);
	if(checkTType(TOKEN_INT)) {
		nextToken();
		node->addChild(array());
		if(node->getNodeType() != EPSIOLN) {
			nextToken();
		}
		if(checkTType(IDENTIFIER)) {
			return node;
		}
	} else {
		node->setRuleType(ERROR_RULE);
		return node;
	}
}
Node* Parser::array() {
	Node* node = new Node(currToken->getType(), ARRAY);
	if(checkTType(SIGN_SQUARE_BRACKET_ON)) {
		nextToken();
		if(checkTType(INTEGER)) {
			nextToken();
			if(checkTType(SIGN_SQUARE_BRACKET_CLOSE)) {
				return node;
			}
		}
	} else {
		node->setRuleType(EPSIOLN);
		return node;
	}
	error();
}
Node* Parser::statements() {
	Node* node = new Node(currToken->getType(), STATEMENTS);
	if(first(STATEMENT)) {
		node->addChild(statement());
		nextToken();
		if(checkTType(SIGN_SEMICOLON)) {
			node->addChild(statements());
			return node;
		}
	} else if(first(EPSIOLN)) {
		node->setRuleType(EPSIOLN);
		return node;
	}
	error();
}
Node* Parser::statement() {
	Node* node = new Node(currToken->getType(), STATEMENT);
	if(checkTType(IDENTIFIER)) {
		nextToken();
		if(first(INDEX)) {
			node->addChild(index());
			nextToken();
			if(checkTType(SIGN_COLON_EQUAL)) {
				node->addChild(exp());
				return node;
			}
		}
	} else if(checkTType(TOKEN_WRITE)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			node->addChild(exp());
			nextToken();
			if(checkTType(SIGN_BRACKET_CLOSE)) {
				return node;
			}
		}
	} else if(checkTType(TOKEN_READ)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			nextToken();
			if(checkTType(IDENTIFIER)) {
				node->addChild(index());
				nextToken();
				if(checkTType(SIGN_BRACKET_CLOSE)) {
					return node;
				}
			}
		}
	} else if(checkTType(SIGN_CURLY_BRACKET_ON)) {
		node->addChild(statements());
		nextToken();
		if(checkTType(SIGN_CURLY_BRACKET_CLOSE)) {
			return node;
		}

	} else if(checkTType(TOKEN_IF)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			node->addChild(exp());
			nextToken();
			if(checkTType(SIGN_BRACKET_CLOSE)) {
				node->addChild(statement());
				nextToken();
				if(checkTType(TOKEN_ELSE)) {
					node->addChild(statement());
					return node;
				}
			}
		}
	} else if(checkTType(TOKEN_WHILE)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			node->addChild(exp());
			nextToken();
			if(checkTType(SIGN_BRACKET_CLOSE)) {
				node->addChild(statement());
				return node;
			}
		}
	}
	error();
}
Node* Parser::exp() {
	Node* node = new Node(currToken->getType(), EXP);
	if(first(EXP2)) {
		node->addChild(exp2());
		node->addChild(op_exp());
		return node;
	}
	error();
}
Node* Parser::exp2() {
	Node* node = new Node(currToken->getType(), EXP2);
	if(checkTType(SIGN_BRACKET_ON)) {
		node->addChild(exp());
		nextToken();
		if(checkTType(SIGN_BRACKET_CLOSE)) {
			return node;
		}
	} else if(checkTType(IDENTIFIER)) {

	} else if(checkTType(INTEGER)) {

	} else if(checkTType(SIGN_MINUS)) {

	} else if(checkTType(SIGN_EXCLEMATION)) {

	}
}
Node* Parser::index() {
	Node* node = new Node(currToken->getType(), INDEX);
}
Node* Parser::op_exp() {

}
Node* Parser::op() {

}
Node* Parser::epsilon() {

}


void Parser::nextToken() {
	currToken = scanner->nextToken();
}
bool Parser::first(RuleType ruleType) {
	switch(ruleType) {
		case NO_RULE:

			break;
		case PROG:

			break;
		case DECLS:

			break;
		case DECL:
			return currToken->getType() == TOKEN_INT;
			break;
		case ARRAY:
			return currToken->getType() == SIGN_SQUARE_BRACKET_ON;
			break;
		case STATEMENTS:

			break;
		case STATEMENT:
			return currToken->getType() == IDENTIFIER ||
					currToken->getType() == TOKEN_WRITE ||
					currToken->getType() == TOKEN_READ ||
					currToken->getType() == SIGN_CURLY_BRACKET_ON ||
					currToken->getType() == TOKEN_IF ||
					currToken->getType() == TOKEN_WHILE;
			break;
		case EXP:

			break;
		case EXP2:
			return currToken->getType() == SIGN_BRACKET_ON ||
					currToken->getType() == IDENTIFIER ||
					currToken->getType() == INTEGER ||
					currToken->getType() == SIGN_MINUS ||
					currToken->getType() == SIGN_EXCLEMATION;
			break;
		case INDEX:
			return currToken->getType() == SIGN_SQUARE_BRACKET_ON;
			break;
		case OP_EXP:

			break;
		case OP:
			return currToken->getType() == SIGN_PLUS ||
					currToken->getType() == SIGN_MINUS ||
					currToken->getType() == SIGN_MULTIPLIER ||
					currToken->getType() == SIGN_COLON ||
					currToken->getType() == SIGN_SMALLER ||
					currToken->getType() == SIGN_GREATER ||
					currToken->getType() == SIGN_EQUAL ||
					currToken->getType() == SIGN_SPECIAL2 ||
					currToken->getType() == SIGN_AND ||
					currToken->getType() == SIGN_SPECIAL;
			break;
		case EPSIOLN:

			break;
	}
}
bool Parser::checkTType(TType tType) {
	return currToken->getType() == tType;
}

void Parser::error() {

}
Node* Parser::createNode() {

}
