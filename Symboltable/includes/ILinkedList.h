#ifndef ILINKEDLIST_H_
#define ILINKEDLIST_H_

#include "../../Automat/includes/Token.h"

class ILinkedList {
public:
	virtual ~ILinkedList(){}

	//folgend: Methoden, die von einer späteren Implementierung geerbt werden müssen

	// nach Tutorial unter: http://www.tutorialspoint.com/cplusplus/cpp_interfaces.htm
	// pure virtual functions providing interface framework.

	   virtual Token* addLast (Token* l) = 0;
	   virtual Token* getToken (int index) = 0;
	   virtual int getSize () = 0;
};

#endif /* ILINKEDLIST_H_ */
