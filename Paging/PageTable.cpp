#include <iostream>
#include <vector>
#include "PageTable.h"
using namespace std;

PageTable::PageTable(int log, int phys)
// constructor
// Assumes: log is the number of pages in the page table
//          phys is the number of frames in physical memory
// Results: creates and initializes the entries in the page table
{
	numStored = 0;
	pageMap.resize(log);

	for (int i = phys - 1; i >= 0; i--) {
		freeFrames.push_back(i); // Utilize a vector to simulate dynamic memory allocation and access.
	}
}

bool PageTable::isValid(int pageNum)
// Assumes: 0 <= pageNum < page table size
// Returns: true if valid bit is set for that index, else false
{
	return pageMap[pageNum].valid;
}

void PageTable::accessPage(int pageNum)
// Assumes: 0 <= pageNum < page table size
// Returns: the frame number where pageNum is stored
{
	cout << pageNum << ": page found at frame " << pageMap[pageNum].frameNumber << endl;
}

void PageTable::storePage(int pageNum)
// Assumes: 0 <= pageNum < page table size
// Results: stores pageNum in a free frame, updating the table
{
	int frameNum;
	if (freeFrames.empty()) {
		int swapPage = selectSwapPage();
		pageMap[swapPage].valid = false;
		frameNum = pageMap[swapPage].frameNumber;
		cout << pageNum << ": PAGE FAULT -- swapping page " << pageNum << " into frame "
			<< frameNum << endl << "   ";
	}
	else {
		frameNum = freeFrames.back();
		freeFrames.pop_back();
		cout << pageNum << ": PAGE FAULT -- inserting page " << pageNum << " into frame "
			<< frameNum << endl << "   ";
	}

	pageMap[pageNum].frameNumber = frameNum;
	pageMap[pageNum].timeStamp = numStored; // Increment time stamp
	pageMap[pageNum].valid = true;

	numStored++; // Increment time stamp counter
}

int PageTable::selectSwapPage()
// Assumes: at least one page is stored in the table
// Returns: index of the oldest page in the table
{
	int oldPage, oldTime = numStored;
	for (int i = 0; i < pageMap.size(); i++) { // Iterate through the pageMage vector
		if (pageMap[i].valid && pageMap[i].timeStamp < oldTime) { // If the bit is set and 
			oldTime = pageMap[i].timeStamp;
			oldPage = i;
		}
	}
	return oldPage;
}