#include "readFile.h"

#include <fstream>		// ifstream

using namespace std;

vector<int> readFile::readInputFile(char* fileName)
{
	vector<int> pages;		// vector to hold all pages

	// read in file
	ifstream file;
	file.open(fileName);

	int newPage = 0;

	if (file.is_open())
	{
		while (file >> newPage)			// while there are new pages to insert
		{
			pages.push_back(newPage);	// insert
		}
	}
	else
	{
		// error opening file
		cout << "File not found.." << endl;
		system("pause");
		exit(0);		// end program?
	}

	file.close();		// close file
	return pages;		// return the vector filled with the page reference string
}


