#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <vector>
using namespace std;

class algorithm
{
public:
	void FIFO(vector<int> pages, int frameSize);
	void LRU(vector<int> pages, int frameSize);
	void LFU(vector<int> pages, int frameSize);
	void optimal(vector<int> pages, int frameSize);
	int findOptimal(vector<int> pages, vector<int> &memory, int index);
	vector<int> frequency(vector<int> pages);
	void saveToFile(string name, int pageFaults, float rate2, float rate4, float rate6, float rate8, float rate10);
	bool search(int key, vector<int> &memory);
};


#endif // ALGORITHM_H

