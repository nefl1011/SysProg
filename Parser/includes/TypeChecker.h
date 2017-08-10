#ifndef TYPECHECKER_H_
#define TYPECHECKER_H_

#include "../includes/Node.h"

class TypeChecker {
private:

public:
	TypeChecker();
	~TypeChecker();

	Node* typeCheck(Node* rootNode);
};

#endif /* TYPECHECKER_H_ */
