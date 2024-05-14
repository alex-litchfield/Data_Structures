#include <iostream>
#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y",".");

	std::cout << "Initial board:" << std::endl << b << std::endl;
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;

	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;

	b.insert(1,false);
	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	b.insert(1,false);
	b.insert(1,true);
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	b.insert(4,true);
	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;

	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
}

////////STUDENT CODE//////

//Write your own test cases here
void StudentTest(){
	//tests win condition and adding rows (one char)
	std::cout << "TESTING WIN CONDITIONS AND ADDING ROWS WITH ONE CHARACTER PER TOKEN" << std::endl;
	Board b("R","Y",".");
	std::cout << "Initial board:" << std::endl << b << std::endl;
	b.insert(0,true);
	b.insert(0,true);
	b.insert(0,true);
	b.insert(0,true);
	b.insert(0,true);
	std::string result=b.insert(0,true);
	std::cout << "Board is now" << std::endl << b << std::endl;
	if(result == "."){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	//tests win condition and adding cols (one char)
	std::cout << "TESTING WIN CONDITIONS AND ADDING COLUMNS WITH ONE CHARACTER PER TOKEN" << std::endl;
	Board b2("R","Y",".");
	std::cout << "Initial board:" << std::endl << b2 << std::endl;
	b2.insert(0,true);
	b2.insert(1,true);
	b2.insert(2,true);
	b2.insert(3,true);
	b2.insert(6,true);
	result=b2.insert(4,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "."){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	//tests win condition and adding rows (five char) 
	std::cout << "TESTING WIN CONDITIONS AND ADDING ROWS WITH FIVE CHARACTERS PER TOKEN" << std::endl;
	Board b3("Puppy","Kitty","-----"); 
	std::cout << "Initial board:" << std::endl << b3 << std::endl;
	b3.insert(0,true);
	b3.insert(0,true);
	b3.insert(0,true);
	b3.insert(0,true);
	b3.insert(0,true);
	result=b3.insert(0,true);
	std::cout << "Board is now" << std::endl << b3 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	//tests win condition and adding cols (five char)
	std::cout << "TESTING WIN CONDITIONS AND ADDING COLUMNS WITH FIVE CHARACTERS PER TOKEN" << std::endl;
	Board b4("Puppy","Kitty","-----"); 
	std::cout << "Initial board:" << std::endl << b4 << std::endl;
	b4.insert(0,true);
	b4.insert(1,true);
	b4.insert(2,true);
	b4.insert(3,true);
	b4.insert(8,true);
	b4.insert(9,true);
	b4.insert(10,true);
	b4.insert(11,true);
	b4.insert(12,true);
	b4.insert(13,true);
	b4.insert(14,true);
	b4.insert(15,true);
	b4.insert(16,true);
	result=b4.insert(4,true);
	std::cout << "Board is now" << std::endl << b4 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}

	std::cout << "COPY TEST BEGINS" << std::endl;
	Board c1("Puppy","Kitty","-----"); 
	c1.insert(2,true);
	std::cout << "c1 Board (before copy):" << std::endl << c1 << std::endl;
	Board c2("Pup","Kit","---"); 
	std::cout << "C2 Board (before copy):" << std::endl << c2 << std::endl;
	c1=c2;
	std::cout << "C1 Board (after copy):" << std::endl << c1 << std::endl;
	std::cout << "C2 Board (after copy):" << std::endl << c2 << std::endl;
	c1.insert(0,true);
	std::cout << "C1 Board (after copy and insertion" << std::endl << c1 << std::endl;
	std::cout << "C2 Board (after copy and insertion" << std::endl << c2 << std::endl;
	
}

