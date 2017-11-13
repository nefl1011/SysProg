#include "../includes/TokenNode.h"

TokenNode::TokenNode(Token* data, TokenNode* next, TokenNode* previous) {
	this->data = data;
	this->next = next;
	this->previous = previous;
}

TokenNode::~TokenNode() {
	delete data;
	delete next;
	delete previous;
}
