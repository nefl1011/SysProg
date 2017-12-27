#ifndef NODE_H_
#define NODE_H_

#include "../../Automat/includes/Token.h"
#include "NodeType.h"
#include "RuleType.h"

class Node {
private:
	Token* token;
	TType tType;
	RuleType ruleType;
	NodeType nodeType;

	bool leaf;

	Node* children[9];
	int childrenCounter = 0;

public:
	Node(Token* token, RuleType ruleType);
	~Node();

	void addChild(Node* child);

	Token* getToken();
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

	void setToken(Token* aToken);
};

#endif /* NODE_H_ */
