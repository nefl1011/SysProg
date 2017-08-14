#include <fstream>

#include "../includes/Scanner.h"
#include "../../Automat/includes/Token.h"

void clearOutputFile(const char *outFilename) {
    ofstream ofs;
    ofs.open(outFilename, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.is_open()) {
        cerr << "Error! Cannot write to output file <" << outFilename << ">" << endl;
        exit(EXIT_FAILURE);
    }
    ofs.close();
}

int main(int argc, char **argv) {

	char* inFile = (char*) "test.txt";
    char* outFilename = (char*) "out.txt";

    try {
    	Scanner* scanner = new Scanner(inFile);

        clearOutputFile(outFilename);

        ofstream result(outFilename, std::ios_base::app);
        cout << "Processing...\n" << endl;
        Token* token;

        while(scanner->hasNextToken()) {
        	token = scanner->nextToken();

        	if (token->getType() == ERROR) {
        		cerr << "unknown Token Line: " << token->getLine() + 1 <<  "\t Column: " << token->getColumn() + 1 << "\t " ;
        		if (!strcmp(token->getLexem(), "Identifier too long")
        				|| !strcmp(token->getLexem(), "Integer out of range")
						|| !strcmp(token->getLexem(), "Lexem too long")) {
        			cerr << token->getLexem() << "\n" << endl;
        		}
        		else {
        			cerr << "Symbol: " << token->getLexem() << "\n" << endl;
        		}
        	}
        	else {
        		if (result.is_open()) {
        			if (token->getType() == IDENTIFIER) {
        				result << "Token " << token->getTypeName() << "\nLine: " << token->getLine() + 1
								<< "\t Column: " << token->getColumn() + 1 << "\t Lexem: " << token->getLexem() << "\n" << endl;
        			}
        			else if (token->getType() == INTEGER) {
        				result << "Token " << token->getTypeName() << "\nLine: " << token->getLine() + 1
								<< "\t Column: " << token->getColumn() + 1 << "\t Value: " << token->getValue() << "\n" << endl;
        			}
        			else if (token->getType() != END_OF_FILE) {
        				result << "Token " << token->getTypeName() << "\nLine: " << token->getLine() + 1
								<< "\t Column: " << token->getColumn() + 1 << "\t Sign: " << token->getLexem() << "\n" << endl;
        			}
        		}
        		else {
        			cerr << "Error!" << " Cannot write to output file <" << outFilename << ">" << endl;
        			exit(EXIT_FAILURE);
        		}
        	}
        }

        cout << "Finished!" << endl << "Output written to <" << outFilename << ">\n" << endl;
        result.close();
    }
    catch (std::exception &ex) {
        cerr << "Error! Cannot read input file <" << inFile << ">" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
