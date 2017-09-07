#include <iostream>
#include <fstream>

#include "../includes/Node.h"
#include "../includes/TypeChecker.h"

using namespace std;

TypeChecker::TypeChecker(char* errorOutFile) {
	this->errorOutFile = errorOutFile;

	ofstream errStream(errorOutFile, std::ios_base::app);
	errStream << "type checking ...\n" << endl;
}

TypeChecker::~TypeChecker() {

}

Node* TypeChecker::typeCheck(Node* rootNode) {
	return typeCheckProg(rootNode);
}

void TypeChecker::analyze(Node* node) {

    if(node == 0L) {
        cout << "node is null" << endl;
        return;
    }

    cout << "analyze: " << node->ruleTypeToString() << endl;
    switch(node->getRuleType()) {
        case PROG:
            typeCheckProg(node);
            break;
        case DECLS:
            typeCheckDecls(node);
            break;
        case EPSILON:
        	typeCheckEmpty(node);
        	break;
        case DECL:
            typeCheckDecl(node);
            break;
        case ARRAY:
            typeCheckArray(node);
            break;
        case STATEMENTS:
            typeCheckStatements(node);
            break;
        case STATEMENT:
        	typeCheckStatement(node);
        	break;
        case EXP:
            typeCheckExp(node);
            break;
        case EXP2:
        	typeCheckExp2(node);
        	break;
        case INDEX:
            typeCheckIndex(node);
            break;
        case OP_EXP:
            typeCheckOp_Exp(node);
            break;
        case OP:
			typeCheckOp(node);
			break;
        case LEAF:
        	break;
        default:
            cerr << "node is empty" << endl;
    }
}


//PROG ::= DECLS STATEMENTS
Node* TypeChecker::typeCheckProg(Node *root) {
    Node* decls = root->getChildren(0);
    Node* statements = root->getChildren(1);

    analyze(decls);
    analyze(statements);

    root->setNodeType(NO_TYPE);

    return root;
}


//DECLS ::= DECL ; DECLS
void TypeChecker::typeCheckDecls(Node* node) {
    Node* decl = node->getChildren(0);
    Node* decls = node->getChildren(1);

    analyze(decl);
    analyze(decls);

    node->setNodeType(NO_TYPE);
}

void TypeChecker::typeCheckEmpty(Node* node) {
    node->setNodeType(NO_TYPE);
}

//DECL::= int ARRAY identifier
void TypeChecker::typeCheckDecl(Node *node) {
    Node* array = node->getChildren(0);
    Node* identifier = node->getChildren(1);

	analyze(array);

	if(identifier && array) {
		if(identifier->getNodeType() != NO_TYPE) {
			//todo error(„identifier already defined“);
			node->setNodeType(NODE_ERROR);
		} else if(array->getNodeType() == NODE_ERROR) {
			node->setNodeType(NODE_ERROR);

		} else {
			node->setNodeType(NO_TYPE);

			if (array->getNodeType() == INT_ARRAY) {
				identifier->setNodeType(INT_ARRAY);
			} else {
				identifier->setNodeType(INT);
			}
		}
	}
}

//ARRAY::=[integer]
void TypeChecker::typeCheckArray(Node* node) {
    Node* integer = node->getChildren(0);

    if(integer) {
    	if(integer->getTType() == INTEGER) {
			node->setNodeType(INT_ARRAY);
		} else {
			// todo error(„no valid dimension“);
			node->setNodeType(NODE_ERROR);
		}
    }
}

//STATEMENTS ::= STATEMENT_IDENTIFIER ; STATEMENTS)
void TypeChecker::typeCheckStatements(Node *node) {
    Node* statement = node->getChildren(0);
    Node* statements = node->getChildren(1);

    analyze(statement);
    analyze(statements);

    node->setNodeType(NO_TYPE);
}

void TypeChecker::typeCheckStatement(Node *node) {
	if(node == 0L) {
		cout << "node is null" << endl;
		return;
	}
	switch(node->getTType()) {
			case IDENTIFIER:
				typeCheckStatement_IDENTIFIER(node);
				break;
			case TOKEN_WRITE:
				typeCheckStatement_WRITE(node);
				break;
			case TOKEN_READ:
				typeCheckStatement_READ(node);
				break;
			case SIGN_CURLY_BRACKET_ON:
				typeCheckStatement_BRACES(node);
				break;
			case TOKEN_IF:
				typeCheckStatement_IF(node);
				break;
			case TOKEN_WHILE:
				typeCheckStatement_WHILE(node);
				break;
		}
}

//STATEMENT_IDENTIFIER ::= identifier INDEX := EXP
void TypeChecker::typeCheckStatement_IDENTIFIER(Node *node) {

    Node* identifier = node->getChildren(0);
    Node* exp = node->getChildren(2);
    Node* index = node->getChildren(1);

    analyze(exp);
    analyze(index);

    if(identifier && exp && index) {
    	if (identifier->getNodeType() == NO_TYPE) {
			node->setNodeType(NODE_ERROR);
			//todo error(„identifier not defined“);
		} else if (exp->getNodeType() == INT && (
				(identifier->getNodeType() == INT && index->getNodeType() == NO_TYPE)
				||(identifier->getNodeType() == INT_ARRAY && index->getNodeType() == INT_ARRAY))) {
			node->setNodeType(NO_TYPE);

		} else {
			//todo error(„incompatible types“);
			node->setNodeType(NODE_ERROR);
		}
    }

}

//STATEMENT_IDENTIFIER ::= write( EXP )
void TypeChecker::typeCheckStatement_WRITE(Node *node) {
    Node* exp = node->getChildren(0);
    analyze(exp);
    node->setNodeType(NO_TYPE);
}

//STATEMENT_IDENTIFIER ::= read( identifier INDEX)
void TypeChecker::typeCheckStatement_READ(Node *node) {
    Node* identifier = node->getChildren(0);
    Node* index = node->getChildren(1);

    analyze(index);

    if(identifier && index) {
    	if (identifier->getNodeType() == NO_TYPE) {
    		// todo error(„identifier not defined“);
			node->setNodeType(NODE_ERROR);
		} else if (((identifier->getNodeType() == INT) && (index->getNodeType() == NO_TYPE))
				   || ((identifier->getNodeType() == INT_ARRAY) && (index->getNodeType() == INT_ARRAY)) ) {
			node->setNodeType(NO_TYPE);

		} else {
			// todo error(„incompatible types“);
			node->setNodeType(NODE_ERROR);
		}
    }

}

//STATEMENT_IDENTIFIER ::= { STATEMENTS }
void TypeChecker::typeCheckStatement_BRACES(Node *node) {
    Node* statements = node->getChildren(0);
    analyze(statements);
    node->setNodeType(NO_TYPE);
}

//STATEMENT_IDENTIFIER ::= if ( EXP ) STATEMENT_IDENTIFIER else STATEMENT_IDENTIFIER
void TypeChecker::typeCheckStatement_IF(Node *node) {
    Node* exp = node->getChildren(0);
    Node* statement1 = node->getChildren(1);
    Node* statement2 = node->getChildren(2);

    analyze(exp);
    analyze(statement1);
    analyze(statement2);

    if(exp) {
    	if(exp->getNodeType() == NODE_ERROR) {
			node->setNodeType(NODE_ERROR);
		} else {
			node->setNodeType(NO_TYPE);
		}
    }

}

//STATEMENT_IDENTIFIER ::= while ( EXP ) STATEMENT_IDENTIFIER)
void TypeChecker::typeCheckStatement_WHILE(Node *node) {
    Node* exp = node->getChildren(0);
    Node* statement = node->getChildren(1);

    analyze(exp);
    analyze(statement);

    if(exp) {
    	if(exp->getNodeType() == NODE_ERROR) {
			node->setNodeType(NODE_ERROR);
		} else {
			node->setNodeType(NO_TYPE);
		}
    }
}

//EXP ::= EXP2_PARENS OP_EXP
void TypeChecker::typeCheckExp(Node* node) {
    Node* exp2 = node->getChildren(0);
    Node* op_exp = node->getChildren(1);

    analyze(exp2);
    analyze(op_exp);

    if(exp2 && op_exp) {
    	if (op_exp->getNodeType() == NO_TYPE) {
			node->setNodeType(exp2->getNodeType());

		} else if (exp2->getNodeType() != op_exp->getNodeType()) {
			node->setNodeType(NODE_ERROR);

		} else {
			node->setNodeType(exp2->getNodeType());
		}
    }
}

void TypeChecker::typeCheckExp2(Node* node) {
	if(node == 0L) {
		cout << "node is null" << endl;
		return;
	}
	switch(node->getTType()) {
		case SIGN_BRACKET_ON:
			typeCheckExp2_SIGN_BRACKET_ON(node);
			break;
		case IDENTIFIER:
			typeCheckExp2_IDENTIFIER(node);
			break;
		case INTEGER:
			typeCheckExp2_INTEGER(node);
			break;
		case SIGN_MINUS:
			typeCheckExp2_MINUS(node);
			break;
		case SIGN_EXCLEMATION:
			typeCheckExp2_EXCLEMATION(node);
			break;
	}
}
//INDEX ::= [ EXP ]
void TypeChecker::typeCheckExp2_SIGN_BRACKET_ON(Node *node) {
    Node* exp = node->getChildren(0);
    analyze(exp);
    node->setNodeType(exp->getNodeType());
}
//EXP2_PARENS ::= identifier INDEX
void TypeChecker::typeCheckExp2_IDENTIFIER(Node *node) {
    Node* index = node->getChildren(1);
    Node* identifier = node->getChildren(0);

    analyze(index);

    if(identifier && index) {
    	if (identifier->getNodeType() == NO_TYPE) {
    		// todo error(„identifier not defined“);
			node->setNodeType(NODE_ERROR);
		} else if (identifier->getNodeType() == INT
				   && index->getNodeType() == NO_TYPE) {
			node->setNodeType(identifier->getNodeType());
		} else if (identifier->getNodeType() == INT_ARRAY
				   && index->getNodeType() == INT_ARRAY) {
			node->setNodeType(INT);
		} else {
			// todo error(„no primitive Type“);
			node->setNodeType(NODE_ERROR);
		}
    }

}
//EXP2_PARENS ::= integer
void TypeChecker::typeCheckExp2_INTEGER(Node *node) {
    node->setNodeType(INT);
}
//EXP2_PARENS ::= - EXP2_PARENS
void TypeChecker::typeCheckExp2_MINUS(Node *node) {
    Node* exp2 = node->getChildren(0);
    analyze(exp2);
    node->setNodeType(exp2->getNodeType());
}

//EXP2_PARENS ::= ! EXP2_PARENS
void TypeChecker::typeCheckExp2_EXCLEMATION(Node *node) {
    Node* exp2 = node->getChildren(0);

    analyze(exp2);

    if(exp2) {
    	if (exp2->getNodeType() != INT) {
			node->setNodeType(NODE_ERROR);
		} else {
			node->setNodeType(INT);
		}
    }
}

//OP_EXP ::= OP_PLUS EXP
void TypeChecker::typeCheckOp_Exp(Node* node) {
    Node* op = node->getChildren(0);
    Node* exp = node->getChildren(1);

    analyze(op);
    analyze(exp);

    node->setNodeType(exp->getNodeType());
}
void TypeChecker::typeCheckOp(Node* node) {
	if(node == 0L) {
		cout << "node is null" << endl;
		return;
	}
	switch(node->getTType()) {
		case SIGN_PLUS:
			typeCheckOp_PLUS(node);
			break;
		case SIGN_MINUS:
			typeCheckOp_MINUS(node);
			break;
		case SIGN_MULTIPLIER:
			typeCheckOp_MULTIPLIER(node);
			break;
		case SIGN_COLON:
			typeCheckOp_COLON(node);
			break;
		case SIGN_SMALLER:
			typeCheckOp_SMALLER(node);
			break;
		case SIGN_GREATER:
			typeCheckOp_GREATER(node);
			break;
		case SIGN_EQUAL:
			typeCheckOp_EQUAL(node);
			break;
		case SIGN_AND:
			typeCheckOp_AND(node);
			break;
		case SIGN_SPECIAL:
			typeCheckOp_SPECIAL(node);
			break;
	}
}

void TypeChecker::typeCheckOp_PLUS(Node *node) {
    node->setNodeType(OP_PLUS_TYPE);
}


void TypeChecker::typeCheckOp_MINUS(Node *node) {
    node->setNodeType(OP_MINUS_TYPE);
}

void TypeChecker::typeCheckOp_MULTIPLIER(Node *node) {
    node->setNodeType(OP_MULT_TYPE);
}

void TypeChecker::typeCheckOp_COLON(Node *node) {
    node->setNodeType(OP_COL_TYPE);
}

void TypeChecker::typeCheckOp_SMALLER(Node *node) {
    node->setNodeType(OP_SMALLER_TYPE);
}

void TypeChecker::typeCheckOp_GREATER(Node *node) {
    node->setNodeType(OP_GREATER_TYPE);
}

void TypeChecker::typeCheckOp_EQUAL(Node *node) {
    node->setNodeType(OP_EQUAL_TYPE);
}

void TypeChecker::typeCheckOp_SPECIAL(Node *node) {
    node->setNodeType(OP_SPECIAL_TYPE);
}

void TypeChecker::typeCheckOp_AND(Node *node) {
    node->setNodeType(OP_AND_TYPE);
}

//INDEX ::= [ EXP ]
void TypeChecker::typeCheckIndex(Node* node) {
    Node* exp = node->getChildren(0);

    analyze(exp);

    if(exp) {
    	if(exp->getNodeType() == NODE_ERROR) {
			node->setNodeType(NODE_ERROR);
		} else {
			node->setNodeType(INT_ARRAY);
		}
    }
}
