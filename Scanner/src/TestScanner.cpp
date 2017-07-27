#include "../includes/Scanner.h"
#include "../../Automat/includes/Token.h"

int main(int argc, char **argv) {

	Buffer*  buffer = new Buffer( (char*) "/home/nefl1011/workspace/SysProg/Buffer/src/TestText01.txt");
	Automat* automat = new Automat();

	Scanner* scanner = new Scanner(buffer, automat);

	Token* token;

	while(scanner->hasNextToken()) {
		token = scanner->nextToken();

		if (token->getType() == ERROR) {
			cout << "Error: Das Zeichen \'" << token->getLexem() << "\' wird nicht akzeptiert!" << endl;
		}
		else if (token->getType() == IDENTIFIER) {
			cout << "Token " << token->getTypeName() << " Line: " << token->getLine()
							<< " Spalte: " << token->getColumn() << " Lexem: " << token->getLexem() << endl;
		}
		else if (token->getType() == INTEGER) {
			cout << "Token " << token->getTypeName() << " Line: " << token->getLine()
							<< " Spalte: " << token->getColumn() << " Value: " << token->getValue() << endl;
		}
		else {
			cout << "Token " << token->getTypeName() << " Line: " << token->getLine()
							<< " Spalte: " << token->getColumn() << " Sign: " << token->getLexem() << endl;
		}
	}


}

