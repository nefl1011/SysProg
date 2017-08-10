#include <iostream>

#include "../includes/Parser.h"

using namespace std;

Parser::Parser(Scanner* scanner) {
	this->scanner = scanner;
}

Parser::~Parser() {
	delete scanner;
}

Node* Parser::parse() {
	return new Node();
}
