#ifndef TokenNODE_H_
#define TokenNODE_H_

#include "../../Automat/includes/Token.h"

class TokenNode {
public:
	Token* data;
	TokenNode* next;
	TokenNode* previous;
	int index;

	TokenNode(Token* data, TokenNode* next, TokenNode* previous);
	virtual ~TokenNode();
};

#endif /* TokenNODE_H_ */
