#include "../includes/Scanner.h"

int main(int argc, char **argv) {

	Buffer*  buffer = new Buffer( (char*) "/home/nick/workspace/SysProgV2/Buffer/src/TestText01.txt");
	Automat* automat = new Automat();

	Scanner* scanner = new Scanner(buffer, automat);

	while(scanner->hasNextToken()) {
		scanner->nextToken();
	}


}

