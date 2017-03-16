/*
 * Automat.h
 *
 *  Created on: 23.04.2015
 *      Author: nefl1011
 */

#ifndef AUTOMAT_H_
#define AUTOMAT_H_
#include <cstring>
#include <iostream>

#include "TTypes.h"

using namespace std;

class Automat {
private:
	TType* states;
	char currentChar;
	int currentIndex;
public:

	Automat();
	~Automat();

	void reset();
	TType currentState();
	void setNextState(int index);
	TType proofInput(char input);
	int getState();
	TType operators(char sign);
	int isInLang(char str);

};


#endif /* AUTOMAT_H_ */
