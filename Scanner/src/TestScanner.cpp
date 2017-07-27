#include "../includes/Scanner.h"
#include "../../Automat/includes/Token.h"

int main(int argc, char **argv) {

	Buffer*  buffer = new Buffer( (char*) "/home/nick/workspace/SysProg/Buffer/src/TestText01.txt");
	Automat* automat = new Automat();

	Scanner* scanner = new Scanner(buffer, automat);

	Token* token;

	while(scanner->hasNextToken()) {
		token = scanner->nextToken();

		if (token->getType() == ERROR) {
			cout << "Error: Das Zeichen \'" << token->getLexem() << "\' wird nicht akzeptiert! \n" << endl;
		}
		else if (token->getType() == IDENTIFIER) {
			cout << "Token " << token->getTypeName() << "\nLine: " << token->getLine()
							<< "\t Spalte: " << token->getColumn() << "\t Lexem: " << token->getLexem() << "\n" << endl;
		}
		else if (token->getType() == INTEGER) {
			cout << "Token " << token->getTypeName() << "\nLine: " << token->getLine()
							<< "\t Spalte: " << token->getColumn() << "\t Value: " << token->getValue() << "\n" << endl;
		}
		else {
			cout << "Token " << token->getTypeName() << "\nLine: " << token->getLine()
							<< "\t Spalte: " << token->getColumn() << "\t Sign: " << token->getLexem() << "\n" << endl;
		}
	}


}

