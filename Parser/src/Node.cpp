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

RuleType Node::getRuleType() {
	return ruleType;
}
NodeType Node::getNodeType() {
	return nodeType;
}
Node** Node::getChildren() {
	return this->children;
}

void Node::setRuleType(RuleType ruleType) {
	this->ruleType = ruleType;
}
