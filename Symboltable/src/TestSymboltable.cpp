#include "../../Symboltable/includes/Symboltable.h"
#include "../../Automat/includes/Token.h"

int main(int argc, char **argv) {

	Symboltable* symboltable;

	Token* token;

	char* string = "test";

	symboltable = new Symboltable();


	token = new Token(IDENTIFIER, string, 0, 0);

	token = symboltable->insertToken(token);

	token = symboltable->insertToken(token);

}


