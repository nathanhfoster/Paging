#include <iostream>
#include <vector>
#include "PageTable.h"
#include <iomanip>
using namespace std;

PageTable::PageTable(int log, int phys){
// constructor
// Utilize a pageMap vector to simulate dynamic memory allocation and access.
// Assumes: log is the number of pages in the page table
//          phys is the number of frames in physical memory
// Results: creates and initializes the entries in the page table
	pageMap.resize(log); // Maximum size of the vector
	//iter_swap(pageMap.begin(), pageMap.begin() + 1);
	
	for (int i = phys - 1; i >= 0; i--) {
		freeFrames.push_back(i); // Allocate room for the physical memory
	}
}

bool PageTable::isValid(int pageNum){
// Assumes: 0 <= pageNum < page table size
// Returns: true if valid bit is set for that index, else false

	return pageMap[pageNum].valid;
}

void PageTable::accessPage(int pageNum){
// Assumes: 0 <= pageNum < page table size
// Returns: the frame number where pageNum is stored

	cout << pageNum << ": page found at frame " << pageMap.at(pageNum).frameNumber << endl;
}

void PageTable::storePage(int pageNum){
// Assumes: 0 <= pageNum < page table size
// Results: stores pageNum in a free frame, updating the table

	int frameNum;
	if (freeFrames.empty()) { // If there is no room in the physical memory
		int swapPage = selectSwapPage(); // Swap page
		pageMap[swapPage].valid = false;
		frameNum = pageMap[swapPage].frameNumber;
		cout << pageNum << ": PAGE FAULT -- swapping page " << pageNum << " into frame "
			<< frameNum << endl;
	}
	else { // Else remove one free frame from the physical memory
		frameNum = freeFrames.back(); // frameNum = freeFrames last element
		freeFrames.pop_back(); // Delete last element
		cout << pageNum << ": PAGE FAULT -- inserting page " << pageNum << " into frame "
			<< frameNum << endl;
	}

	pageMap.at(pageNum).frameNumber = frameNum;
	pageMap[pageNum].timeStamp = numStored; // Increment time stamp
	pageMap[pageNum].valid = true;

	numStored++; // Increment time stamp counter
	printTables();
}

int PageTable::selectSwapPage() {
// Assumes: at least one page is stored in the table
// Returns: index of the oldest page in the table

	int oldPage, oldTime = numStored;
	for (int i = 0; i < pageMap.size(); i++) { // Iterate through the pageMap vector
		if (pageMap[i].valid && pageMap[i].timeStamp < oldTime) { // If the bit is set and time stamp is the smallest
			oldTime = pageMap[i].timeStamp;
			oldPage = i;
		}
	}
	return oldPage;
}


void PageTable::printTables() {
	/* setfill(x) fill the empty space by provided character x   */
	/* setw(x) creates a column of width x                       */
	/* left keyword align the contents of a columns left align   */
	/* right keyword align the contents of a columns right align */

	// printing top border
	cout << left << setfill('-') << setw(1) << "+" << setw(4) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(9) << setfill('-') << "-" << right << "+" << setfill(' ')<< setw(21) << "+" << setfill('-') << setw(15) << "-" << endl;
	// printing table record
	cout << right << setw(1) << "|" << "ADR" << setfill(' ') << setw(2) << "|" << left << setw(15) << "Page" << setw(1) << "|" << setw(15)  << "Valid" << setw(1) << "|" << setw(5) << "TimeStamp" << setw(1) << "|" << setw(20) << setfill(' ') << " " << "|" << "Free Frames" << setw(4) << right << "|" << endl;
	// printing bottom border
	cout << setfill('-') << setw(4) << "+" << setw(17) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(20) << setfill(' ') << " " << setw(1) << setfill(' ') << "+" << setfill('-') << setw(15) << "-" << endl;
	for (unsigned int i = 0; i < pageMap.size(); i++)
	{
		// printing table record
		cout << "|" << setfill(' ') << setw(3) << i << setfill(' ') << setw(1) << " " << "|" << setw(15) << pageMap.at(i).frameNumber
			<< setw(1) << "|" << setw(15) << pageMap.at(i).valid << setw(1) << "|" << setw(5)
			<< pageMap.at(i).timeStamp << setfill(' ') << setw(4) << " " << setw(1) << "|";
		// conditionally print the free frames
		if (i < freeFrames.size()) {
			cout << left << setw(20) << setfill(' ') << " " << "|" << setw(5) << freeFrames.at(i) << setfill(' ') << setw(9) << " " << setw(1) << "|" <<endl;
			//printing bottom border
			cout << setfill('-') << setw(4) << "+" << setw(17) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << setw(20) << setfill(' ') << " " << setw(1) << setfill(' ') << "+" << setfill('-') << setw(15) << "-" << endl;
		}
		// if there wasn't a frame printed don't forget to print the bottom border
		else {
			// printing bottom border
			cout << endl << setfill('-') << setw(4) << "+" << setw(17) << "-" << setw(1) << "+" << setw(15) << "-" << setw(1) << "+" << setw(9) << "-" << setw(1) << "+" << endl;
		}
	}

}

/*
printf("-5s%-%-20i%-20i%-20i%-20i%\n", "     ", i, pageMap.at(i).frameNumber, pageMap.at(i).valid, pageMap.at(i).timeStamp);
if (i < freeFrames.size()) {
	printf("%-20i%-20i%-20s%\n-20s%\n", i, freeFrames.at(i), "|--------------------------------|", "|--------------------------------|");
}
else {
	printf("%-20s%\n", "   |--------------------------------|");
}
*/
