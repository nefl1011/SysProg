#include <iostream>

#include "../includes/Buffer.h"

using namespace std;

Buffer::Buffer(char* path) {
	this->filePath = path;

	ungetJump = 0;
	bufferSize = 512;

	//Buffer erzeugen
	buffer1 = new char[bufferSize];
	buffer2 = new char[bufferSize];

	//Speicher für die Buffer allokieren
	posix_memalign( (void**) &buffer1, bufferSize, bufferSize );
	posix_memalign( (void**) &buffer2, bufferSize, bufferSize );

	//Zeiger setzen
	pointerBuffer1 = &buffer1[0];
	pointerBuffer2 = &buffer2[0];
	current = &buffer1[0];
	next = &buffer1[0];

	//Datei öffnen
	file = open(this->filePath, O_DIRECT);
	if(file == -1) {
		cout << "Fehler beim Öffnen der Datei!" << endl;
	} else {
		//Buffer1 füllen
		read(file, pointerBuffer1, bufferSize);

		fileEnd = 0;
	}

}

Buffer::~Buffer() {
	delete buffer1;
	delete buffer2;
}

char Buffer::getChar() {
	//Setzt das nächste Zeichen als aktuelles Zeichen
	current = next;

	//Wenn das letzte Zeichen von Buffer1 erreicht ist:
	if(current == pointerBuffer1 + bufferSize - 1) {

		if(ungetJump == 1) {
			next = pointerBuffer2;
			ungetJump = 0;
			return *current;
		}

		//Buffer2 füllen
		read(file, pointerBuffer2, bufferSize);

		next = pointerBuffer2;
		return *current;
	}
	//Wenn das letzte Zeichen von Buffer2 erreicht ist:
	if(current == pointerBuffer2 + bufferSize - 1) {

		if(ungetJump == 1) {
			next = pointerBuffer1;
			ungetJump = 0;
			return *current;
		}

		//Buffer1 füllen
		read(file, pointerBuffer1, bufferSize);

		next = pointerBuffer1;
		return *(current);
	}
	//Wenn sich der Zeiger im Buffer1 oder Buffer2 befindet
	next++;

	//Eliminiert eine Escapesequence/Zeichenliteral und gibt stattdessen ein Leerzeichen zurück
	if(/**current == '\n'   ||*/ *current == '\r' || *current == '\t' ||  *current == '\v' ||
	   *current == '\b' || *current == '\f' ||
	   *current == '\a') {
		return ' ';
	}
//	char c = *current;
//	if(!(c == '\n' || ((int)c >= 47 && (int)c <= 62) ||
//		((int)c >= 40 && (int)c <= 43) || ((int)c >= 65 && (int)c <= 91) ||
//		((int)c >= 97 && (int)c <= 123) || (int)c == 93 || (int)c == 125 ||
//		(int)c == 33 || (int)c == 38  || c == '-' || c == ' ')) {
//		return ' ';
//	}
	//Setzt fileEnd auf TRUE, wenn es kein Zeichen mehr gibt
	if(*next == '\0') {
		fileEnd = 1;
	}

	return *current;
}
void Buffer::ungetChar() {

	if(current == pointerBuffer1) {
		next = pointerBuffer2 + bufferSize - 1;
		ungetJump = 1;
	}
	else if(current == pointerBuffer2) {
		next = pointerBuffer1 + bufferSize - 1;
		ungetJump = 1;
	}
	else {
		next--;
	}
	current = next;

}

int Buffer::hasNext() {
	return !fileEnd;
}

