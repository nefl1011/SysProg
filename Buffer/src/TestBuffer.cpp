#include "../includes/Buffer.h"


int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer( (char*) "/home/nick/workspace/SysProgV2/Buffer/src/TestText01.txt");

	while(buffer->hasNext()) {
		cout << buffer->getChar();
	}

}
