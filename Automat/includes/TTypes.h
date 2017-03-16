/*
 * TTypes.h
 *
 *  Created on: 23.04.2015
 *      Author: nefl1011
 */

#ifndef TTYPES_H_
#define TTYPES_H_

#include <cstring>
#include <iostream>
using namespace std;

enum TType {
	error = 0,		//Falsche Eingabe
	integer = 1,	//Zahlen
	identifier = 2,	//Bezeichner
	sign = 3,		//Operatoren
	pluS = 4,
	minuS = 5,
	mul = 6,
	divide = 7,
	greateR = 8,
	lesS = 9,
	equaL = 10,
	anD = 11,
	semicolon = 12,
	bracketOn = 13,
	bracketClose = 14,
	curlyBracketOn = 15,
	curlyBracketClose = 16,
	squareBracketOn = 17,
	squareBracketClose = 18,
	colon = 19,
	assign = 20,
	comment = 21,	//Kommentare
	normalState = 22,//normaler Zustand
	tokenIf = 23,
	tokenWhile = 24
};

class Token {
private:
	TType type;
	int line;
	int column;
	char* lexem;
	int value;

public:
	Token(TType type, char* lexem, int line, int column);
	~Token();
	TType getType();
	char* getLexem();
	int getLine();
	int getColumn();
	int getValue();

};


#endif /* TTYPES_H_ */
