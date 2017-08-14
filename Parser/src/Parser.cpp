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
	if(first(DECLS)) {
		node->addChild(decls());
	}
	if(first(STATEMENTS)) {
		node->addChild(statements());
		return node;
	}
	if(currToken == NULL) {
		return node;
	}
	error();
}
Node* Parser::decls() {
	Node* node = new Node(currToken->getType(), DECLS);
	if(first(DECL)) {
		node->addChild(decl());
		if(checkTType(SIGN_SEMICOLON)) {
			nextToken();
			if(first(DECLS)) {
				node->addChild(decls());
			}
			return node;
		}
	}
	error();
}
Node* Parser::decl() {
	Node* node = new Node(currToken->getType(), DECL);
	if(checkTType(TOKEN_INT)) {
		nextToken();
		if(first(ARRAY)) {
			node->addChild(array());
		}
		if(checkTType(IDENTIFIER)) {
			nextToken();
			return node;
		}
	}
	error();
}
Node* Parser::array() {
	Node* node = new Node(currToken->getType(), ARRAY);
	if(checkTType(SIGN_SQUARE_BRACKET_ON)) {
		nextToken();
		if(checkTType(INTEGER)) {
			nextToken();
			if(checkTType(SIGN_SQUARE_BRACKET_CLOSE)) {
				nextToken();
				return node;
			}
		}
	}
	error();
}
Node* Parser::statements() {
	Node* node = new Node(currToken->getType(), STATEMENTS);
	if(first(STATEMENT)) {
		node->addChild(statement());
		if(checkTType(SIGN_SEMICOLON)) {
			nextToken();
			if(first(STATEMENTS)) {
				node->addChild(statements());
			}
			return node;
		}
	}
	error();
}
Node* Parser::statement() {
	Node* node = new Node(currToken->getType(), STATEMENT);
	if(checkTType(IDENTIFIER)) {
		nextToken();
		if(first(INDEX)) {
			node->addChild(index());
		}
		if(checkTType(SIGN_COLON_EQUAL)) {
			nextToken();
			if(first(EXP)) {
				node->addChild(exp());
				return node;
			}
		}
	} else if(checkTType(TOKEN_WRITE)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			nextToken();
			if(first(EXP)) {
				node->addChild(exp());
				if(checkTType(SIGN_BRACKET_CLOSE)) {
					nextToken();
					return node;
				}
			}
		}
	} else if(checkTType(TOKEN_READ)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			nextToken();
			if(checkTType(IDENTIFIER)) {
				nextToken();
				if(first(INDEX)) {
					node->addChild(index());
				}
				if(checkTType(SIGN_BRACKET_CLOSE)) {
					nextToken();
					return node;
				}
			}
		}
	} else if(checkTType(SIGN_CURLY_BRACKET_ON)) {
		nextToken();
		if(first(STATEMENTS)) {
			node->addChild(statements());
		}
		if(checkTType(SIGN_CURLY_BRACKET_CLOSE)) {
			return node;
		}

	} else if(checkTType(TOKEN_IF)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			nextToken();
			if(first(EXP)) {
				node->addChild(exp());
				if(checkTType(SIGN_BRACKET_CLOSE)) {
					nextToken();
					if(first(STATEMENT)) {
						node->addChild(statement());
						if(checkTType(TOKEN_ELSE)) {
							nextToken();
							if(first(STATEMENT)) {
								node->addChild(statement());
								return node;
							}
						}
					}
				}
			}

		}
	} else if(checkTType(TOKEN_WHILE)) {
		nextToken();
		if(checkTType(SIGN_BRACKET_ON)) {
			nextToken();
			if(first(EXP)) {
				node->addChild(exp());
				if(checkTType(SIGN_BRACKET_CLOSE)) {
					nextToken();
					if(first(STATEMENT)) {
						node->addChild(statement());
						return node;
					}
				}
			}
		}
	}
	error();
}
Node* Parser::exp() {
	Node* node = new Node(currToken->getType(), EXP);
	if(first(EXP2)) {
		node->addChild(exp2());
		if(first(OP_EXP)) {
			node->addChild(op_exp());
		}
		return node;
	}
	error();
}
Node* Parser::exp2() {
	Node* node = new Node(currToken->getType(), EXP2);
	if(checkTType(SIGN_BRACKET_ON)) {
		nextToken();
		if(first(EXP)) {
			node->addChild(exp());
			if(checkTType(SIGN_BRACKET_CLOSE)) {
				nextToken();
				return node;
			}
		}
	} else if(checkTType(IDENTIFIER)) {
		nextToken();
		if(first(INDEX)) {
			node->addChild(index());
		}
		return node;
	} else if(checkTType(INTEGER)) {
		nextToken();
		return node;
	} else if(checkTType(SIGN_MINUS)) {
		nextToken();
		if(first(EXP2)) {
			node->addChild(exp2());
			return node;
		}
	} else if(checkTType(SIGN_EXCLEMATION)) {
		nextToken();
		if(first(EXP2)) {
			node->addChild(exp2());
			return node;
		}
	}
	error();
}
Node* Parser::index() {
	Node* node = new Node(currToken->getType(), INDEX);
	if(checkTType(SIGN_SQUARE_BRACKET_ON)) {
		nextToken();
		if(first(EXP)) {
			node->addChild(exp());
			if(checkTType(SIGN_SQUARE_BRACKET_CLOSE)) {
				nextToken();
				return node;
			}
		}
	}
}
Node* Parser::op_exp() {
	Node* node = new Node(currToken->getType(), OP_EXP);
	if(first(OP)) {
		node->addChild(op());
		if(first(EXP)) {
			node->addChild(exp());
			return node;
		}
	}
	error();
}
Node* Parser::op() {
	Node* node = new Node(currToken->getType(), OP);
	if(checkTType(SIGN_PLUS) || checkTType(SIGN_MINUS) || checkTType(SIGN_MULTIPLIER) ||
			checkTType(SIGN_COLON) || checkTType(SIGN_SMALLER) || checkTType(SIGN_GREATER) ||
			checkTType(SIGN_EQUAL) || checkTType(SIGN_AND) || checkTType(SIGN_SPECIAL)) {
		nextToken();
		return node;
	}
	error();
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
			return first(DECL);
			break;
		case DECL:
			return currToken->getType() == TOKEN_INT;
			break;
		case ARRAY:
			return currToken->getType() == SIGN_SQUARE_BRACKET_ON;
			break;
		case STATEMENTS:
			return first(STATEMENT);
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
			return first(EXP2);
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
			return first(OP);
			break;
		case OP:
			return currToken->getType() == SIGN_PLUS ||
					currToken->getType() == SIGN_MINUS ||
					currToken->getType() == SIGN_MULTIPLIER ||
					currToken->getType() == SIGN_COLON ||
					currToken->getType() == SIGN_SMALLER ||
					currToken->getType() == SIGN_GREATER ||
					currToken->getType() == SIGN_EQUAL ||
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
	cout << "ERROR!!!" << endl;
}