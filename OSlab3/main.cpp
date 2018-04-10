#include <iostream>
#include <fstream>
#include <iomanip>
#include "readFile.h"
#include "algorithm.h"

using namespace std;

// unix prompt format, first is name of program, second is frame size, thrid is input file, fourth is output file
// memsim		128		input.dat		output.dat

char* inputFile;			// input file name
char* outputFile;			// output file name **** output file name has to be output.dat
readFile r;					// readInputFile is member funtino of class readFile
vector<int> pageOrder;		// vector to hold order of page references
algorithm a;				// algorithm class
int frameSize = 3;				// frame size

int main(int argc, char* argv[])
{
	if (argc)
	{
		frameSize = atoi(argv[1]);
		inputFile = argv[2];
		outputFile = argv[3];
	}


	pageOrder = r.readInputFile(inputFile);		// get the vector of page references

	// save only the header part of the output to the output file
	ofstream outFile;
	outFile.open("output.dat");
	if (outFile.is_open())
	{
		outFile << "======================================================" << endl;
		outFile << "        Page Replacement Algorithm Simulation (frame size = " << frameSize << ")" << endl;
		outFile << "======================================================" << endl;
		outFile << "			                 	Page fault rates	" << endl;
		outFile << " Algorithm   Total Page Faults " << setw(10) << "2000" << setw(10) << "4000" << setw(10) << "6000"  
			<< setw(10) << "8000" << setw(10) << "10000 " << endl;
		outFile << "-----------------------------------------------------------------------------------------------------------" << endl;
	}
	else
	{
		cout << "File not found.." << endl;
		exit(0);		// end program
	}

	outFile.close();

	a.FIFO(pageOrder, frameSize);
	a.LRU(pageOrder, frameSize);
	a.LFU(pageOrder, frameSize);
	a.optimal(pageOrder, frameSize);
}