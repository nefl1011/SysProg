#include <fstream>

#include "../includes/ParseTree.h"

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
	char* inFile = (char*) "Scannertest.txt";
	char* outFile = (char*) "out.txt";

	try {
		ParseTree* parseTree = new ParseTree(inFile, outFile);

        cout << "Processing...\n" << endl;

		cout << "Parsing...\n" << endl;
		parseTree->parse();

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
