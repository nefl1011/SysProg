#ifndef NODE_H_
#define NODE_H_

#include "NodeType.h"
#include "RuleType.h"

class Node {
private:
	NodeType nodeType;
	RuleType ruleType;

public:
	Node();
	~Node();
};

#endif /* NODE_H_ */
