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
	current = &buffer1[0];
	next = &buffer1[0];

	//Datei öffnen
	file = open(this->filePath, O_DIRECT);
	if(file == -1) {
		cerr << "Fehler beim Öffnen der Datei!" << endl;
	} else {
		//Buffer1 füllen
		read(file, buffer1, bufferSize);

		if (*next == '\0') {
			cerr << "Document is empty!" << endl;
			fileEnd = 1;
		}
		else {
			fileEnd = 0;
		}
	}

}

Buffer::~Buffer() {
	delete buffer1;
	delete buffer2;
	delete current;
	delete filePath;
	delete next;
}

char Buffer::getChar() {
	//Setzt das nächste Zeichen als aktuelles Zeichen
	current = next;

	//Wenn das letzte Zeichen von Buffer1 erreicht ist:
	if(current == buffer1 + bufferSize - 1) {

		if(ungetJump == 1) {
			next = buffer2;
			ungetJump = 0;
			return *current;
		}

		//Buffer2 füllen
		read(file, buffer2, bufferSize);

		next = buffer2;
		return *current;
	}
	//Wenn das letzte Zeichen von Buffer2 erreicht ist:
	if(current == buffer2 + bufferSize - 1) {

		if(ungetJump == 1) {
			next = buffer1;
			ungetJump = 0;
			return *current;
		}

		//Buffer1 füllen
		read(file, buffer1, bufferSize);

		next = buffer1;
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

	//Setzt fileEnd auf TRUE, wenn es kein Zeichen mehr gibt
	if(*next == '\0') {
		fileEnd = 1;
	}

	return *current;
}
void Buffer::ungetChar() {

	if(current == buffer1 + bufferSize - 1) {
		next = buffer1 + bufferSize - 1;
		ungetJump = 1;
	}
	else if(current == buffer2 + bufferSize - 1) {
		next = buffer2 + bufferSize - 1;
		ungetJump = 1;
	}
	else {
		next--;
	}
	if (fileEnd) {
		fileEnd = 0;
	}
	current = next;

}

int Buffer::hasNext() {
	return !fileEnd;
}

