#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "../../Automat/includes/Token.h"
#include "TokenLinkedList.h"

class HashMap {

private:
	TokenLinkedList* table;
	int size;

public:
	HashMap(int size);
	~HashMap();

	bool insertToken(Token* t);
	int hashcode(char *lexem, int length);

	TType getTokenType(char* lexem);

	 /* Gibt die Länge eines Wortes zurück
	 */
	static int length(char *lexem);

	/*
	 * Vergleiche Lexem mit gespeicherten
	 * Wort im Element
	 */
	static bool compare(char *lexem1, const char *lexem2);

};

#endif /* HASHMAP_H_ */
