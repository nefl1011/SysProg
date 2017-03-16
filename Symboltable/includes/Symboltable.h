/*
 * SymTable.hpp
 *
 *  Created on: 15.04.2015
 *      Author: eriksteigert
 */

#ifndef SYMTABLE_HPP_
#define SYMTABLE_HPP_

#include <string>
#include "Information.h"

using namespace std;

class SymTable {

private:
	int tableSize;
	const char* initialValue;

	struct symtabEntry {
		symtabEntry* next;
		Information* info;

	};

	symtabEntry* hashTable[];


public:
	SymTable(int size);
	int hash(const char* Key, int length);
	const char* insert(const char* lexem, TType typ);
	Information* lookup(const char* key);

};


#endif /* SYMTABLE_HPP_ */

