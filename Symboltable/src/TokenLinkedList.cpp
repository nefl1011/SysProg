#include "../includes/TokenLinkedList.h"
#include <iostream>	//für debugging-Zwecke

TokenLinkedList::TokenLinkedList() {
	first = 0;	//Nullpointer
	last = 0;	//Nullpointer
	size = 0;

	//Testcode folgend
	//addLast(*(new Token(*new String ("int"), integer)));
}

TokenLinkedList::~TokenLinkedList() {
	for (int i = 0; i < getSize(); i++) {
		getTokenNode(i)->~TokenNode();
	}
}

Token* TokenLinkedList::addLast(Token* l) {

	TokenNode* oldlast = last;
	last = new TokenNode(l, (TokenNode*) 0, oldlast);//neues Last-Element wird erstellt

	//wenn Liste vor Aufruf der Methode größer als 0 war, war ein altes "last"-Element vorhanden.
	//Oldlast ist somit != Nullpointer und Oldlast's next Attribut muss somit umgebogen werden auf
	//unser neues "last"-Element
	if (oldlast != 0) {
		oldlast->next = last;
		last->index += 1;
	} else {	//die TokenLinkedList war leer vor Aufruf der Methode
		first = last;
	}
	size++;
	return l;
}
Token* TokenLinkedList::getToken(int index) {

	if (first == 0)
		return 0;

	TokenNode* runner = first;

	while (index > 0) {
		runner = runner->next;
		index--;
	}

	return runner->data;
}

int TokenLinkedList::getSize() {
	return size;
}
TokenNode* TokenLinkedList::getTokenNode(int index) {
	TokenNode* result = first;
	if (!(index > getSize() || index < 0)) {
		for (int i = 0; i < getSize(); i++) {
			if (i != index) {
				result = result->next;
			} else {
				break;
			}
		}
	}
	return result;
}
