/*
 * Scanner.cpp
 *
 *  Created on: 24.04.2015
 *      Author: nefl1011
 */

#include <iostream>
using namespace std;

#include "../includes/Scanner.h"
#include "../../Automat/includes/Automat.h"
#include "../../Automat/includes/Token.h"

int nStates = 0;

Scanner::Scanner(char* path) {
	this->path = path;
	this->buffer = new Buffer(this->path);
	this->automat = new Automat();
	this->typeScanner = automat->currentState();
	this->current = '\0';
	this->lexemS;
	this->lexemLength = 0;
	this->lineS = 1;
	this->columnS = 1;
}

Scanner::~Scanner() {
	delete automat;
	delete buffer;
}

Token* Scanner::nextToken() {
	int counter = 1;
	char* lexemScanner = new char[512];
	int col = columnS;
	int lin = lineS;
	TType lastRegStat = this->automat->currentState();

//	prüft Eingabe und speichert zwischen
	while (buffer->hasNext() & typeScanner != error) {
		current = buffer->getChar();
		//Zeichen in Sprache vorhanden?
		if (!automat->isInLang(current)) {
			return nextToken();
		}


		//hier werden leerzeichen zwischen zwei seperaten identifieren übersprungen! Darf nicht sein!
/**->*/	while (current == ' ') {
			current = buffer->getChar();
			columnS++;
		}



		//überprüfe Zeichen
		typeScanner = automat->proofInput(current);

		//speicher die Zeichen ab
		lexemScanner[lexemLength] = current;

		//zähle alle normalen Zustände
		if (typeScanner == normalState) {
			counter++;
		} //speichere letzten regulären Zustand
		else if (typeScanner != error) {
			lastRegStat = typeScanner;
		}

		lexemLength++;
		columnS++;

	}
//	Automat zurücksetzen
	automat->reset();
	typeScanner = automat->currentState();

//	zurückgehen bis normal
	if (current != '\n') {
		while (counter != 0) {
			counter--;
			lexemLength--;
			columnS--;
			buffer->ungetChar();
		}
	}//Zeilenumbrüche vermeiden
	else {
		lineS++;
		columnS = 1;
		counter--;
		lexemLength--;
	}

//	Lexembildung
	lexemS = new char[lexemLength + 1];
	for (int i = 0; i < lexemLength; i++) {
		lexemS[i] = lexemScanner[i];
	}
	lexemS[lexemLength] = '\0';
	lexemLength = 0;

//	Lexem in Stringtabelle

//	Tokenbildung

	//Ich weiß zwar nicht warum man es nur hier einsetzen kann, aber es funktioniert irgendwie :D
	if (lastRegStat == normalState || lastRegStat == comment) {
		return nextToken();
	}
	Token* t = new Token(lastRegStat, this->lexemS, lin, col);

//	Token in Symboltabelle
//	if (lastRegStat == identifier) {
//		insert(...);
//		return get(...);
//	}

	return t;
}

int Scanner::hasNext() {
	return this->buffer->hasNext();
}







