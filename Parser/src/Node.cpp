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
NodeType Node::getNodeType() {
	return nodeType;
}

void Node::setRuleType(RuleType ruleType) {
	this->ruleType = ruleType;
}
