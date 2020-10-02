// Sudoku Solver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
vector<int> sudokuGrid{};
vector<int> completedGrid{ 0 };
unsigned int startCondtion{ 0 };
void printArray(vector<int>);
bool validateGrid();
bool emptyCells();
bool uniqueInVector(vector<int>);
bool recusSolve(bool);


int main(){
	 sudokuGrid = {	6,7,2,  0,3,0,  9,4,0,
					8,0,0,  6,0,0,  0,7,5, 
					0,0,9,  8,2,0,  6,0,0, 
					1,0,0,  0,0,0,  0,2,0, 
					0,0,0,  0,0,8,  7,5,0, 
					2,8,4,  7,5,3,  1,0,9, 
					7,0,3,  1,8,0,  0,0,0, 
					4,0,5,  0,0,0,  3,0,0, 
					0,0,0,  3,7,4,  0,0,6 };
	 if (validateGrid() == false) {
		 cout << "the inputted grid has errors, check entry!" << endl;
		 return 0;
	}
	cout << "The starting Grid is: " << endl;
	cout << "Total entries in Grid: " << sudokuGrid.size() << endl;

	printArray(sudokuGrid);
	
	if (validateGrid()) {
		cout << "grid is valid" << endl;
		recusSolve(true);
		printArray(completedGrid);
	}
	else {
		cout << "INVALID GRID" << endl;
	}
	
    
}

void printArray(vector<int> sudokuGrid) {
	int i{ 1 };

	for (const auto& cell : sudokuGrid) {
		//Do something for each one
		cout << cell << " ";
		
		if (i % 9 == 0) {
			cout << endl;
		}
		i++;
	}

}

bool recusSolve(bool test) {
	if (test == true) {
		for (int i{ 0 }; i < sudokuGrid.size(); i++) {
			//cout << "value at " << i << " is " << sudokuGrid.at(i) << endl;
			if (sudokuGrid.at(i) == 0) {
				for (int j{ 1 }; j < 10; j++) {
					sudokuGrid.at(i) = j;

					if (validateGrid()) {
						recusSolve(true);
					}
					if (emptyCells() == false && validateGrid()) {
						completedGrid = sudokuGrid;
					}
					sudokuGrid.at(i) = 0;
					
				}
				return false;
			}

		}
	}
}
	

bool validateGrid() {
	
	for (int i{ 0 }; i < 9; i++) {
		
		//loop though the "row" so i +1 9 times
		
		vector<int> v{0,0,0, 0,0,0, 0,0,0 };
		for (int j{ 0 }; j < 9; j++) {
			v.at(j) = sudokuGrid.at((i*9) + j);
		}
		//set this row
		if (uniqueInVector(v)) {

		}
		else {
			return false;
		}
		

	}
	//validate columns
	for (int i{ 0 }; i < 9; i++) {

		//loop though the "row" so i +1 9 times

		vector<int> v{ 0,0,0, 0,0,0, 0,0,0 };
		for (int j{ 0 }; j < 9; j++) {
			v.at(j) = sudokuGrid.at((j * 9) + i);
		}
		//set this row
		if (uniqueInVector(v)) {

		}
		else {
			return false;
		}

	}


	//validate Cubes 
	vector<int> offsets{ 0,3,27,30,33,54,57,60 };
	for (const auto& offset : offsets) {
		vector<int> v{};

		//Top line of mini grid
		v.push_back(sudokuGrid.at(0 + offset));
		v.push_back(sudokuGrid.at(1 + offset));
		v.push_back(sudokuGrid.at(2 + offset));
		//middle line of mini grid
		v.push_back(sudokuGrid.at(9 + offset));
		v.push_back(sudokuGrid.at(10 + offset));
		v.push_back(sudokuGrid.at(11 + offset));
		//Bottline line of mini grid
		v.push_back(sudokuGrid.at(18 + offset));
		v.push_back(sudokuGrid.at(19 + offset));
		v.push_back(sudokuGrid.at(20 + offset));
		
		if (uniqueInVector(v)) {

		}
		else {
			return false;
		}
	}
	return true;

}

bool emptyCells() {
	for (int i{ 0 }; i < sudokuGrid.size(); i++) {
		if (sudokuGrid.at(i) == 0) {
			return true;
		}
	}
	return false;
}

bool uniqueInVector(vector<int> toTest) {
	for (int i{ 0 }; i < toTest.size(); i++) {
		for (int j{ 0 }; j < toTest.size(); j++) {
			if (i != j) {
				if (toTest.at(i) == toTest.at(j)) {
					if (toTest.at(i) == 0) {
						//False positive found! it's zero!
					}
					else {
						return false;
					}
				}
			}
		}
	}
	return true;
}
