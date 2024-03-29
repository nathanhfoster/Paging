#ifndef _PAGE_TABLE_
#define _PAGE_TABLE_

#include <vector>
using namespace std;

class PageTable{
private:
	int numStored;				// Counter to increment timeStamp
	int selectSwapPage();       // Swap pages when there are no more available frames
	class TableEntry
	{
	public:
		int frameNumber;        // Used to represent content of an address
		int timeStamp;          // Used to flag the least active frames
		bool valid;
		TableEntry() : frameNumber(-1), timeStamp(0), valid(false) { }// Intially set all frames to be invalid
	};
	vector<TableEntry> pageMap; // Used to dynamically write to the physical memory
	vector<int> freeFrames;     // Used as a counter for available addresses in the physical memory
								// freeFrames is a vector because you can use the freeFrames.empty() function call to check availability
public:
	PageTable(int log, int phys);
	bool isValid(int pageNum);
	void accessPage(int pageNum);
	void storePage(int pageNum);
	void printTables();
	PageTable() : numStored(0){}
};

#endif