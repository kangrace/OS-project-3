#include "algorithm.h"
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

void algorithm::FIFO(vector<int> pages, int frameSize)
{
	vector<int> memory;		// vector of memory that has size of frameSize
	vector<int> queue;		// vector to store pages in FIFO (for replacement)
	float rate2 = 0, rate4 = 0, rate6 = 0, rate8 = 0, rate10 = 0;	// holds the page fault rates for 2000, 4000, etc
	int pageFaults = 0;			// total number of page faults
	int firstPage = 0;
	for (unsigned int i = 0; i < pages.size(); i++)		// without the 'unsigned', it gave a warning
	{
		// when i = 2000, means it reached 2000 pages, so store the current number of
		// page faults for each divided by the number of pages to get the rate of page faults
		switch (i)
		{
		case 2000:
			rate2 = (float)pageFaults / 2000;	// cast expressions to floats to get a float back
			break;

		case 4000:
			rate4 = (float)pageFaults / 4000;
			break;

		case 6000:
			rate6 = (float)pageFaults / 6000;
			break;

		case 8000:
			rate8 = (float)pageFaults / 8000;
			break;
		}
		// case 10000 always returns 0 so if there are 10000 pages or more
		// this is 9999 because i starts at 0
		if (i >= 9999)
		{
			rate10 = (float)pageFaults / 10000;
		}

		//  add page to memory only if page is not in memory
		if ((find(memory.begin(), memory.end(), pages[i]) != memory.end()) == false)
		{
			// check if memory can hold more pages
			if (memory.size() < frameSize)
			{
				memory.push_back(pages[i]);		// add it to memory
				pageFaults++;					// + 1 page fault
				queue.push_back(pages[i]);
			}

			// if memory is full, need to replace 
			else
			{
				firstPage = queue.front();		// index = first page in queue
				queue.erase(remove(queue.begin(), queue.end(), firstPage), queue.end());
									// remove first page from queue

				//replace
				// remove the firstpage from memory
				memory.erase(remove(memory.begin(), memory.end(), firstPage), memory.end());
				memory.push_back(pages[i]);			// insert the current page
				queue.push_back(pages[i]);			// add current page to queue too

				pageFaults++;						// + 1 page fault
			}
		}
	}
	string name = "FIFO";
	saveToFile(name, pageFaults, rate2, rate4, rate6, rate8, rate10);	// output results to file
}

void algorithm::LRU(vector<int> pages, int frameSize)
{
	vector<int> memory;		// vector of memory that has size of frameSize
	vector<int> queue(10000);		// the queue of pages

	float rate2 = 0, rate4 = 0, rate6 = 0, rate8 = 0, rate10 = 0;	// holds the page fault rates for 2000, 4000, etc
	int pageFaults = 0;			// total number of page faults

	for(unsigned int i = 0; i < pages.size(); i++)		// without the 'unsigned', it gave a warning
	{
		// when i = 2000, means it reached 2000 pages, so store the current number of
		// page faults for each divided by the number of pages to get the rate of page faults
		switch (i)
		{
		case 2000:
			rate2 = (float)pageFaults / 2000;	// cast expressions to floats to get a float back
			break;

		case 4000:
			rate4 = (float)pageFaults / 4000;
			break;

		case 6000:
			rate6 = (float)pageFaults / 6000;
			break;

		case 8000:
			rate8 = (float)pageFaults / 8000;
			break;
		}
		// case 10000 always returns 0 so if there are 10000 pages or more
		// this is 9999 because i starts at 0
		if (i >= 9999)
		{
			rate10 = (float)pageFaults / 10000;
		}


		//  add page to memory only if page is not in memory
		if ((find(memory.begin(), memory.end(), pages[i]) != memory.end()) == false)
		{
			// check if memory can hold more pages
			if (memory.size() < frameSize)
			{
				memory.push_back(pages[i]);		// add it to memory
				pageFaults++;					// + 1 page fault

				// also, store the indexes of the recently used pages in order
				// so first page inserted will be lru, with value of 0
				// ex: if first page is 6, at queue[6] will be 0.
				queue.at(pages[i]) = i;
			}

			// if memory is full, need to replace 
			else
			{
				// find lru page (smallest index) to replace
				int lru = 100000, index;		// lru initialized to big number, since INT_MAX gives error in csegrid
				for (auto it = memory.begin(); it != memory.end(); it++)
				{
					if (queue.at(*it) < lru)		// if page is going to be used the least
					{
						lru = queue[*it];			// set it as the lru
						index = *it;				// set current counter as new (lru)index
					}
					// and check all pages
				}

				// remove page with smallest index (lru)
				memory.erase(remove(memory.begin(), memory.end(), index), memory.end());
				memory.push_back(pages[i]);			// insert the new page
				pageFaults++;						// + 1 page fault
				queue.at(pages[i]) = i;				// update index for new page

			}
		}
		queue.at(pages[i]) = i;		// update index for page that already existed since it's not LRU anymore too
	}

	string name = "LRU";

	saveToFile(name, pageFaults, rate2, rate4, rate6, rate8, rate10);	// output results to file
}

void algorithm::LFU(vector<int> pages, int frameSize)
{
	float rate2 = 0, rate4 = 0, rate6 = 0, rate8 = 0, rate10 = 0;	// holds the page fault rates for 2000, 4000, etc
	int pageFaults = 0;			// total number of page faults
	vector<int> memory;			// to store the pages
	vector<int> freq = frequency(pages);				// vector of frequencies set by function frequency

	for (unsigned int i = 0; i < pages.size(); i++)		// without the 'unsigned', it gave a warning
	{
		// when i = 2000, means it reached 2000 pages, so store the current number of
		// page faults for each divided by the number of pages to get the rate of page faults
		switch (i)
		{
		case 2000:
			rate2 = (float)pageFaults / 2000;	// cast expressions to floats to get a float back
			break;

		case 4000:
			rate4 = (float)pageFaults / 4000;
			break;

		case 6000:
			rate6 = (float)pageFaults / 6000;
			break;

		case 8000:
			rate8 = (float)pageFaults / 8000;
			break;
		}
		// case 10000 always returns 0 so if there are 10000 pages or more
		// this is 9999 because i starts at 0
		if (i >= 9999)
		{
			rate10 = (float)pageFaults / 10000;
		}

		// insert into memory only if it isn't already
		if (!(find(memory.begin(), memory.end(), pages[i]) != memory.end()))
		{
			// check if memory can hold more pages
			if (memory.size() < frameSize)
			{
				memory.push_back(pages[i]);		// add it to memory
				pageFaults++;					// + 1 page fault
			}
			// else need to replace
			else
			{
				// go through all the frequencies and if the current pages frequency is less 
				// then replace???????????????????????????????????????
				//int lfu = INT_MAX, index;
				//for (auto it = memory.begin(); it != memory.end(); it++)
				//{
				//	//cout << freq.at(*it) << "          ";
				//	//cout << *it << endl;
				//	if (freq.at(*it) < lfu)
				//	{
				//		lfu = freq[*it];
				//		index = *it;
				//	}
				//}

				int lfu = 0;
				// go though all page frequencies
				for (int j = 0; j < memory.size(); j++)
				{
					// find the lowest frequency
					if (freq.at(j) < freq.at(lfu))
					{
						lfu = j;
					}
				}

				// replace page that is lfu
				memory.erase(remove(memory.begin(), memory.end(), memory.at(lfu)), memory.end());
				freq.erase(remove(freq.begin(), freq.end(), memory[lfu]), freq.end());		// remove that frequency too
				memory.insert(memory.begin() + lfu, pages[i]);			// insert the new page
				pageFaults++;						// + 1 page fault

			}
		}
	}

	string name = "LFU";
	saveToFile(name, pageFaults, rate2, rate4, rate6, rate8, rate10);	// output results to file

}

void algorithm::optimal(vector<int> pages, int frameSize)
{
	float rate2 = 0, rate4 = 0, rate6 = 0, rate8 = 0, rate10 = 0;	// holds the page fault rates for 2000, 4000, etc
	int pageFaults = 0;			// total number of page faults

	vector<int> memory;			// to store the pages

	for (unsigned int i = 0; i < pages.size(); i++)		// without the 'unsigned', it gave a warning
	{
		// when i = 2000, means it reached 2000 pages, so store the current number of
		// page faults for each divided by the number of pages to get the rate of page faults
		switch (i)
		{
		case 2000:
			rate2 = (float)pageFaults / 2000;	// cast expressions to floats to get a float back
			break;

		case 4000:
			rate4 = (float)pageFaults / 4000;
			break;

		case 6000:
			rate6 = (float)pageFaults / 6000;
			break;

		case 8000:
			rate8 = (float)pageFaults / 8000;
			break;
		}
		// case 10000 always returns 0 so if there are 10000 pages or more
		// this is 9999 because i starts at 0
		if (i >= 9999)
		{
			rate10 = (float)pageFaults / 10000;
		}

		// insert into memory only if it isn't already
		if (!(find(memory.begin(), memory.end(), pages[i]) != memory.end()))
		{
			// check if memory can hold more pages
			if (memory.size() < frameSize)
			{
				memory.push_back(pages[i]);		// add it to memory
				pageFaults++;					// + 1 page fault
			}
			// else need to replace
			else
			{
				int newIndex = findOptimal(pages, memory, i);	// find new index
				memory[newIndex] = pages[i];					// insert page to new memory index
				pageFaults++;									// + 1 page fault
			}
		}
		
	}
	string name = "Optimal";
	saveToFile(name, pageFaults, rate2, rate4, rate6, rate8, rate10);	// output results to file
}



// function that helps optimal page replacement
// finds the frame that will not be used soon after a certain index
int algorithm::findOptimal(vector<int> pages, vector<int> &memory, int index)
{
	// store index of pages that are going to be used soon
	int optimal = 0;				// variable for optimal index
	int farthest = index;			// find pages after some index 
	for (int i = 0; i < memory.size(); i++)
	{
		int j;
		for (j = index; j < pages.size(); j++)		// check all pages
		{
			if (memory[i] == pages[j])		// if page is equal to current page
			{
				if (j > farthest)			// but it has to be be the farthest page
				{
					farthest = j;			// make sure and check all pages
					optimal = i;			// check all pages in the frame
				}
				break;				// break and check a new page
			}
			
		}

		// if a page is never used again, return that index
		if (j == pages.size())
			return i;
	}
	return optimal;		// return optimal page idex
}

vector<int> algorithm::frequency(vector<int> pages)
{
	vector<int> freq (pages.size());
	int fCount = 0;
	// go through and count each time the page appears
	for (int i = 0; i < pages.size(); i++)
	{
		fCount = count(pages.begin(), pages.end(), pages[i]);
		freq.at(pages[i]) = fCount;	// + 1 frequency
	}

	// returns the frequency vector
	return freq;
}

void algorithm::saveToFile(string name, int pageFaults, float rate2, float rate4, float rate6, float rate8, float rate10)
{
	ofstream outFile;
	outFile.open("output.dat", ios::app);	// app is append to an existing file
	if (outFile.is_open())
	{

		outFile << setw(10) << name << setw(20) << pageFaults << setw(22) << setprecision(3) << rate2 << setw(10) << rate4 
			<< setw(10) << rate6 << setw(10) << rate8 << setw(10) << rate10 << endl;
	}
	//else, no else because it should open since it opened in main first!
	outFile.close();
}

