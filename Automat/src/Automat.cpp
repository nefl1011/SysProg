/*
 * Automat.cpp
 *
 *  Created on: 23.04.2015
 *      Author: nefl1011
 */

#include <iostream>

using namespace std;

#include "../includes/Automat.h"

	Automat::Automat() {
		this->states = new TType[12];
		this->states[0] = normalState;
		this->states[1] = integer;
		this->states[2] = identifier;
		this->states[3] = sign;
		this->states[4] = colon;
		this->states[5] = assign;
		this->states[6] = normalState;
		this->states[7] = normalState;
		this->states[8] = comment;
		this->states[9] = sign;
		this->states[10] = normalState;
		this->states[11] = sign;
		this->currentIndex = 0;
		this->currentChar = '\0';
	}

	Automat::~Automat() {
		delete[] this->states;
	}

	//Der Zustand des Automaten wird auf den Startzustand gesetzt.
	void Automat::reset() {
		setNextState(0);
	}

	//Gibt den momentanen Zustand des Automaten zurück.
	TType Automat::currentState() {
		return this->states[this->currentIndex];
	}

	//Der Zustand des Automaten wird auf einen vorgegebenen Index gesetzt.
	void Automat::setNextState(int index) {
		if (index < 12 && index >= 0) {
			this->currentIndex = index;
		}
		else {
			this->currentIndex = 110;
		}
	}

	//Der Automat überprüft, ob das eingegebene Zeichen vom Automaten
	//im jetztigen Zustand gelesen werden kann.
	TType Automat::proofInput(char c) {
		this->currentChar = c;

		//Übergänge der Zustände
		switch (this->currentIndex){

			//Zustände für <:>
			case 10:
				if (c == '>') {
					setNextState(11);
					return this->states[11];
				}
				break;
			case 9:
				if (c == ':') {
					setNextState(10);
					return this->states[10];
				}
				break;

			//Kommentare
			case 7:
				if (c == ':') {
					setNextState(8);
					return this->states[8];
				}
				else {
					setNextState(6);
					return this->states[6];
				}
				break;
			case 6:
				if (c == '*') {
					setNextState(7);
					return this->states[7];
				}
				else {
					setNextState(6);
					return this->states[6];
				}
				break;

			//Zustände für := oder Kommentare
			case 4:
				if (c == '=') {
					setNextState(5);
					return this->states[5];
				}
				if (c == '*') {
					setNextState(6);
					return this->states[6];
				}
				break;

			case 2:
				if (((((int)c) >= 97 && ((int)c) <= 122) || (((int)c) >= 65 && ((int)c) <= 90)) ||
					 (((int)c) >= 48 && ((int)c) <= 57)) {
					return this->states[2];
				}
				break;

			//Zahlen-Automat
			case 1:
				if (((int)c) >= 48 && ((int)c) <= 57) {
					return this->states[1];
				}
				break;

			//Übergänge des Startzustands
			case 0:
				//Zahlen
				if ((((int)c) >= 48 && ((int)c) <= 57)) {
					setNextState(1);
					return this->states[1];
				}
				//Buchstaben
				else if ((((int)c) >= 97 && ((int)c) <= 122) || (((int)c) >= 65 && ((int)c) <= 90)) {
					setNextState(2);
					return this->states[2];
				}
				//normale Zeichen
				else if (c == '+' || c == '-' || c == '*' || c == '>' || c == '=' || c == '!' || c == '&' ||
						 c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']') {
					setNextState(3);
					return operators(c);
				}
				//Sonderzeichen
				else if (c == ':') {
					setNextState(4);
					return operators(c);
				}
				else if (c == '<') {
					setNextState(9);
					return operators(c);
				}
				break;
			default:
				setNextState(110);
				reset();
				return error;
		}
		reset();
		return error;
	}

	//Gibt den Index des momentanen Zustands wieder.
	int Automat::getState() {
		if (this->currentIndex > 11) {
			return 110;
		}
		return this->currentIndex;
	}

	TType Automat::operators(char sign) {
		if (sign == '+'){
			return pluS;
		} else if (sign == '-') {
			return minuS;
		} else if (sign == '*') {
			return mul;
		} else if (sign == '/') {
			return divide;
		} else if (sign == '>') {
			return greateR;
		} else if (sign == '<') {
			return lesS;
		} else if (sign == '=') {
			return equaL;
		} else if (sign == '&') {
			return anD;
		} else if (sign == ';') {
			return semicolon;
		} else if (sign == '(') {
			return bracketOn;
		} else if (sign == ')') {
			return bracketClose;
		} else if (sign == '{') {
			return curlyBracketOn;
		} else if (sign == '}') {
			return curlyBracketClose;
		} else if (sign == '[') {
			return squareBracketOn;
		} else if (sign == ']') {
			return squareBracketClose;
		} else if (sign == ':') {
			return colon;
		} else {
			return error;
		}

	}

	int Automat::isInLang(char str) {
		return (((int)str >= 47 && (int)str <= 62) ||
				((int)str >= 40 && (int)str <= 43) || ((int)str >= 65 && (int)str <= 91) ||
				((int)str >= 97 && (int)str <= 123) || (int)str == 93 || (int)str == 125 ||
				(int)str == 33 || (int)str == 38  || str == '-' || str == ' ');
	}



