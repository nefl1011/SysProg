#include "../includes/TokenNode.h"

TokenNode::TokenNode(Token* data, TokenNode* next, TokenNode* previous) {
	this->data = data;
	this->next = next;
	this->previous = previous;
}

TokenNode::~TokenNode() {
	// TODO Auto-generated destructor stub
}
