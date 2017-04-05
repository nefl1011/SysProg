#include "../includes/Scanner.h"


#include <iostream>
#include <stdio.h>

#include "../../Buffer/includes/Buffer.h"
#include "../../Automat/includes/Automat.h"

#include "../includes/Scanner.h"
#include "../../Automat/includes/Token.h"
using namespace std;

Buffer* buffer = new Buffer("/home/nefl1011/Schreibtisch/Buffer/TestText.txt");
Automat* automat = new Automat();

Scanner* scan = new Scanner("/home/nefl1011/Schreibtisch/Buffer/TestText.txt");
//Operatoren in String
char* printType(TType type) {
	switch (type) {
	case integer:return "Integer\t";
	break;
	case identifier: return "Identifier";
	break;
	case sign: return "Sign\t";
	break;
	case pluS: return "Plus\t";
	break;
	case minuS: return "Minus\t";
	break;
	case mul: return "Mul\t";
	break;
	case divide: return "Divide\t";
	break;
	case greateR: return "Greater\t";
	break;
	case lesS: return "Less\t";
	break;
	case equaL: return "Equal\t";
	break;
	case anD: return "And\t";
	break;
	case semicolon: return "Semicolon\t";
	break;
	case bracketOn: return "Bracket On";
	break;
	case bracketClose: return "Bracket Close";
	break;
	case curlyBracketOn: return "Curly Bracket On";
	break;
	case curlyBracketClose: return "Curly Bracket Close";
	break;
	case squareBracketOn: return "Square Bracket On";
	break;
	case squareBracketClose: return "Square Bracket Close";
	break;
	case colon: return "Colon\t";
	break;
	case assign: return "Assign\t";
	break;
	case comment: return "Comment\t";
	break;
	default: return "Error\t";
	}
}

int main(int argc, char **argv) {

	Token* t;
	for (int i = 0; i <= 45; i++) {
		t = scan->nextToken();
		cout << "Token "<< printType(t->getType());;
		cout  << "\t";
		if (t->getLine() >= 10) {
			cout << "Line: " << t->getLine() << "\t";
		}
		else {
			cout << "Line: " << t->getLine() << "\t\t";
		}
		cout << "Column: " << t->getColumn() << "\t";
//		if (t->getType() == identifier) {
//			cout << "Lexem: " << t->getLexem() << "\t";
//		}
		if (t->getType() == integer) {
			cout << "Value: " << t->getValue() << "\t";
		}
		else {
			cout << "Lexem: " << t->getLexem() << "\t";
		}
		cout   << endl;
	}


	return 0;
}

