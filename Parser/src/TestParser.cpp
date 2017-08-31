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
	Node** children = node->getChildren();
	int size = sizeof(children);
	for(int i = 0; i <= size; i++) {
		if(children[i] == NULL) {
			continue;
		}
		for(int j = 0; j < treeLevel; j++) {
			cout << "->";
		}
		cout << children[i]->ruleTypeToString() << " (" << children[i]->tTypeToString() << ")";
		if(children[i]->getLeaf()) {
			cout << " --leaf--";
		}
		cout << endl;
		treeLevel++;
		printParseTree(children[i]);
	}
	treeLevel--;
}

int main(int argc, char **argv) {
	char* inFile = (char*) "ParserTestFile.txt";
	char* outFile = (char*) "out.txt";
	char* errorOutFile = (char*) "Parser-error.txt";
	clearOutputFile(outFile);
	clearOutputFile(errorOutFile);

	try {
		ParseTree* parseTree = new ParseTree(inFile, outFile, errorOutFile);

        cout << "Processing...\n" << endl;

		cout << "Parsing...\n" << endl;
		parseTree->parse();
		cout << "------------------------------------------------- ParseTree ---" << endl;
		printParseTree(parseTree->getRootNode());
		cout << "---------------------------------------------------------------\n" << endl;

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
