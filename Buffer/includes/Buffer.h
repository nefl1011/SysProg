/*
 * Buffer.h
 *
 *  Created on: 04.04.2015
 *      Author: Nick Nowak
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Buffer {

	private:
	char* filePath;
	int file;
	int fileEnd;
	int ungetJump;
	unsigned int bufferSize;
	char* buffer1;
	char* buffer2;
	char* pointerBuffer1;
	char* pointerBuffer2;
	char* current;
	char* next;

	public:
	Buffer(char* path);
	~Buffer();

	char getChar();
	void ungetChar();

	int hasNext();

};



#endif /* BUFFER_H_ */
