#include "../includes/HashMap.h"

#include <iostream>
using namespace std;

/*
 * HashMap besteht aus Listen die aus Objekten vom Typ Token bestehen.
 */

HashMap::HashMap(int size) {
	this->size = size;
	this->table = new TokenLinkedList[size];
}

HashMap::~HashMap() {
	delete table;
}


/*
 * insertToken setzt ein Token in die HashMap
 */
bool HashMap::insertToken(Token* t){
	int leng = length(t->getLexem());
	//hashCode des Strings von Token bestimmt die Zeile in der HashMap
	int index = hashcode(t->getLexem(), leng) % this->size;

	this->table[index].addLast(t);
	return true;

}

/*
 * getTokenType nimmt als Argument einen String und durchsucht die HashMap
 * nach einem Objekt vom Typ Token, bei dem dieser String übereinstimmt
 * und gibt den zugehörigen TType zurück
 * String lexem ist hier im Prinzip der Key und der TType der Value
 */
TType HashMap::getTokenType(char* lexem) {
    //Zeile in der HashMap durch hashCode des Strings berechnen
    int index = hashcode(lexem, length(lexem)) % this->size;

    //falls Zeile leer: null
    if (this->table[index].getSize() == 0) {
        return null;
    } else {
        //falls Zeile nicht leer, sequenziell TokenLinkedList nach gesuchtem String durchsuchen
        //und TType des zugehörigen Tokens zurückgeben
        for (int i = 0; i < table[index].getSize(); i++) {

            Token* current = table[index].getToken(i);
            if (compare(current->getLexem(), lexem)) {
                return current->getType();
            }
        }
    }

    return null;
}

int HashMap::hashcode(char *lexem, int length) {
	int hashCode = (16 * lexem[0] + 8 * lexem[length - 1] +length);
	return hashCode % size;
}

bool HashMap::compare(char *lexem1, const char *lexem2) {
    int i = 0;
    while (lexem1[i] != '\0') {
        if (lexem1[i] != lexem2[i]) {
            return false;
        }
        i++;
    }

    return lexem2[i] == '\0';
}

int HashMap::length(char *lexem) {
    int i = 0;
    while (lexem[i] != '\0') {
        i++;
    }
    return i;
}


