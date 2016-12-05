#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string>
#include "PageTable.h"
using namespace std;

int validInput();

int main()
{
    cout << "Enter number of pages in logical memory: ";
	int logSize = validInput();

    cout << "Enter number of frames in physical memory: ";
	int physSize = validInput();

    PageTable PT(logSize, physSize);            // CREATE THE PAGE TABLE

    cout << "Enter the page-reference string "<<"(0-"<< logSize - 1 << ")" << ": ";
	int pageNum = validInput();
	while (pageNum >= logSize) {		// Validate input by staying within the indices of the Page Table.		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Out of range.  Try again: ";
		pageNum = validInput();
	}
    while (pageNum != -1) {                     // REPEAT UNTIL END OF INPUT
        if (PT.isValid(pageNum)) {              // IF PAGE IS IN MEMORY,
            PT.accessPage(pageNum);             //   THEN ACCESS IT
        }
        else {                                  // OTHERWISE,
            PT.storePage(pageNum);              //   SWAP THE PAGE IN 
            PT.accessPage(pageNum);             //   THEN ACCESS IT
        }
		cout << "Enter the page-reference string " << "(0-" << logSize - 1 << ")" << ": ";
		pageNum = validInput();
		while (pageNum >= logSize) {		// Validate input		
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Out of range.  Try again: ";
			pageNum = validInput();
		}

    }

    return 0;
}

int validInput(){
	int input;
	//cin >> input;
	while (!(cin >> input)) { // cin.fail() while input is not an int
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
		//cin >> input;
	}
	if (input < 0) { // If a negative number terminate program.
		cout << "Terminating in..." << endl;
		for (int e = 3; e > 0; e--)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			std::cout << e << "."; std::this_thread::sleep_for(std::chrono::milliseconds(250));
			std::cout << "."; std::this_thread::sleep_for(std::chrono::milliseconds(250));
			std::cout << "."; std::this_thread::sleep_for(std::chrono::milliseconds(250));
			std::cout << std::endl;
		}
		exit(EXIT_FAILURE);
	}
	return input;
}