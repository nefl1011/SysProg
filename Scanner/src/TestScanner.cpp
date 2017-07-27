#include "../includes/Scanner.h"

int main(int argc, char **argv) {

	Buffer*  buffer = new Buffer( (char*) "/home/nefl1011/Schreibtisch/Buffer/TestText.txt");
	Automat* automat = new Automat();

	Scanner* scanner = new Scanner(buffer, automat);

	while(scanner->hasNextToken()) {
		scanner->nextToken();
	}


}

