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
	nextToken();
	if(first(PROG)) {
		return this->prog();
	}
	error();
}

Node* Parser::prog() {
	Node* node = new Node(currToken->getType(), PROG);
	if(first(DECLS)) {
		node->addChild(decls());
	} else {
		node->addChild(epsilon());
	}
	if(first(STATEMENTS)) {
		node->addChild(statements());
		return node;
	} else {
		node->addChild(epsilon());
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
			} else {
				node->addChild(epsilon());
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
		} else {
			node->addChild(epsilon());
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
				node->setLeaf(true);
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
			} else {
				node->addChild(epsilon());
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
		} else {
			node->addChild(epsilon());
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
				} else {
					node->addChild(epsilon());
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
		} else {
			node->addChild(epsilon());
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
		} else {
			node->addChild(epsilon());
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
		} else {
			node->addChild(epsilon());
		}
		return node;
	} else if(checkTType(INTEGER)) {
		node->setLeaf(true);
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
	error();
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
		node->setLeaf(true);
		nextToken();
		return node;
	}
	error();
}
Node* Parser::epsilon() {
	Node* node = new Node(null, EPSILON);
	node->setLeaf(true);
	return node;
}


void Parser::nextToken() {
	currToken = scanner->nextToken();
}
bool Parser::first(RuleType ruleType) {
	switch(ruleType) {
		case NO_RULE:

			break;
		case PROG:
			return first(DECLS) || first(STATEMENTS);
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
		case EPSILON:

			break;
	}
}
bool Parser::checkTType(TType tType) {
	expectedTType = tType;
	return currToken->getType() == tType;
}

void Parser::error() {

	cout << "unexpected Token " << "\t Line: " << currToken->getLine() << " \t Column: "
			<< currToken->getColumn() << " \t " << tTypeToString(currToken->getType())
			<< " \t -> expected Token: " << tTypeToString(expectedTType) << "\n" << endl;
	cout << "stop" << endl;
	exit(0);
}

char* Parser::tTypeToString(TType tType) {
	switch(tType) {
		case ERROR							:	return "Error"; break;
		case INTEGER						:	return "Integer"; break;
		case IDENTIFIER						:	return "Identifier"; break;
		case SIGN_PLUS						:	return "\"+\" (Plus)"; break;
		case SIGN_MINUS						:	return "\"-\" (Minus)"; break;
		case SIGN_MULTIPLIER				:	return "\"*\" (Multiplier)"; break;
		case SIGN_COLON						:	return "\":\" (Colon)"; break;
		case SIGN_GREATER					:	return "\">\" (Greater)"; break;
		case SIGN_SMALLER					:	return "\"<\" (Smaller)"; break;
		case SIGN_EQUAL						:	return "\"=\" (Equal)"; break;
		case SIGN_AND						:	return "\"&&\" (And)"; break;
		case SIGN_SEMICOLON					:	return "\";\" (Semicolon)"; break;
		case SIGN_BRACKET_ON				:	return "\"(\" (Bracket-On)"; break;
		case SIGN_BRACKET_CLOSE				:	return "\")\" (Bracket-Close)"; break;
		case SIGN_CURLY_BRACKET_ON			:	return "\"{\" (Curly-Bracket-On)"; break;
		case SIGN_CURLY_BRACKET_CLOSE		:	return "\"}\" (Curly-Bracket-Close)"; break;
		case SIGN_SQUARE_BRACKET_ON			:	return "\"[\" (Square-Bracket-On)"; break;
		case SIGN_SQUARE_BRACKET_CLOSE		:	return "\"]\" (Square-Bracket-Close)"; break;
		case SIGN_SPECIAL					:	return "\"=:=\" (Special)"; break;
		case SIGN_COLON_EQUAL				:	return "\":=\" (Colon-Equal)"; break;
		case SIGN_EXCLEMATION				:	return "\"!\" (Exclamation)"; break;
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
