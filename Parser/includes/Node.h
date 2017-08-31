#ifndef NODE_H_
#define NODE_H_

#include "../../Automat/includes/Token.h"
#include "NodeType.h"
#include "RuleType.h"

class Node {
private:
	TType tType;
	RuleType ruleType;
	NodeType nodeType;

	bool leaf;

	Node* children[9];
	int childrenCounter = 0;

public:
	Node(TType tType, RuleType ruleType);
	~Node();

	void addChild(Node* child);

	RuleType getRuleType();
	NodeType getNodeType();
	bool getLeaf();
	TType getTType();
	Node* getChildren(int position);
	Node** getChildren();

	void setRuleType(RuleType ruleType);
	void setNodeType(NodeType nodeType);

	void setLeaf(bool leaf);

	char* tTypeToString();
	char* ruleTypeToString();
	char* nodeTypeToString();
};

#endif /* NODE_H_ */
