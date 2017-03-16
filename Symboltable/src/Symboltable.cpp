/*
 * SymTable.cpp
 *
 *  Created on: 15.04.2015
 *      Author: eriksteigert
 */
#include "../includes/Symboltable.h"

using namespace std;

int tableSize;
const char* initialValue;

SymTable::SymTable(int size) {

	this->tableSize = size;
	initialValue = " ";
	for (int i = 0; i < tableSize; i++) {
		hashTable[i] = new symtabEntry;
		hashTable[i]->info = new Information(initialValue, error);
		hashTable[i]->next = NULL;
	}
}


const char* SymTable::insert(const char* lexem, TType typ) {

	int lexlength = strlen(lexem);
	int index = hash(lexem, lexlength);

	if(strcmp(hashTable[index]->info->getName(), initialValue) == 0) {
		hashTable[index]->info->setName(lexem);
		hashTable[index]->info->setType(typ);
	}

	else {
		symtabEntry* ptr = hashTable[index];
		symtabEntry* neu = new symtabEntry;
		neu->info->setName(lexem);
		neu->info->setType(typ);
		while(ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = neu;

	}

	return lexem;
}

Information* SymTable::lookup(const char* key) {
	int lexlength = strlen(key);
	int index = hash(key, lexlength);
	symtabEntry* ptr = hashTable[index];
	bool found;

	while(ptr != NULL) {
		if(strcmp(ptr->info->getName(), key) == 0) {
			found = true;
		}
		ptr = ptr->next;
	}
	if (found) {
		return ptr->info;
	}
	return NULL;
}

int SymTable::hash(const char* Key, int length) {
	int hash = 0;
	int index = 0;

	for (unsigned int i = 0; i < (unsigned int)length; i++) {
		hash += (int)Key[i];
	}
	index = hash % ((this->tableSize)+1);

	return index;
}







