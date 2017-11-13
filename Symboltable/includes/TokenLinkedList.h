#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "TokenNode.h"
#include "ILinkedList.h"

class Token;

class TokenLinkedList: public ILinkedList {
private:
	int size;
	TokenNode* first;
	TokenNode* last;
	TokenNode* getTokenNode(int index);

public:
	TokenLinkedList();
	virtual ~TokenLinkedList();

	bool addLast(Token* l);
	Token* getToken(int index);
	int getSize();
};

#endif /* LINKEDLIST_H_ */
