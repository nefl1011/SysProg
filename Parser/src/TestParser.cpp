#include <fstream>

#include "../includes/ParseTree.h"
#include "../includes/Node.h"

void clearOutputFile(const char *outFilename) {
    ofstream ofs;
    ofs.open(outFilename, std::ofstream::out | std::ofstream::trunc);
    if (!ofs.is_open()) {
        cerr << "Error! Cannot write to output file <" << outFilename << ">" << endl;
        exit(EXIT_FAILURE);
    }
    ofs.close();
}

int treeLevel = 0;
void printParseTree(Node* node) {
	int size = sizeof(node->getChildren());
	Node** children = node->getChildren();
	for(int i = 0; i <= sizeof(children); i++) {

	}

}

int main(int argc, char **argv) {
	char* inFile = (char*) "ParserTestFile.txt";
	char* outFile = (char*) "out.txt";

	try {
		ParseTree* parseTree = new ParseTree(inFile, outFile);

        cout << "Processing...\n" << endl;

		cout << "Parsing...\n" << endl;
		parseTree->parse();
		printParseTree(parseTree->getRootNode());

		cout << "Checking type information...\n" << endl;
		parseTree->typeCheck();

		cout << "Generating code...\n" << endl;
		parseTree->makeCode();

		cout << "Finished!" << endl << "Output written to <" << outFile << ">\n" << endl;
	}
	catch (std::exception &ex) {
        cerr << "Error! Cannot read input file <" << inFile << ">" << endl;
        exit(EXIT_FAILURE);
    }
	return 0;
}
