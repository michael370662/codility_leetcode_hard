#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
/*
* Design a program that verify if there's a single swap that can sort an array after it had a mixed up 
* in order, aka a potential bad swap after a complete sort or a sort that didn't go all the way.
* Example: {8,2,3,4,5,6,7,1} and {1,2,3,6,5,4,7,8,9,} should say yes while {8,3,4,5,1,2,6,7) should say no.
*/

using namespace std;

int solution(int *A, int n) {
	int i;
	int x;
	int y;
	int prev;
	x = -1;
	y = -1;
	prev = A[0];
	for (i = 1; i < n; ++i) {
		if (prev > A[i]) {
			if (x == -1) {
				x = i - 1;
				y = i;
			}
			else{
				/*Second conflict*/
				y = i;
			}

		}		
		prev = A[i];
	}
	swap(A[x], A[y]);
	for (i = 0; i < (n-1); ++i) {/*Verification loop*/
		if (A[i] > A[i + 1]) {
			return 0;
		}
	}
	return 1;
};

int main()
{
	int i;
	int t;
	ifstream inFile;
	stringstream mule;
	inFile.open("1_off_sorted_array.txt");
	try {
		if (!inFile.is_open())
			throw exception("No such file found");
	}
	catch (const exception& error) {
		cerr << error.what() << endl;
		return (EXIT_FAILURE);
	}
	mule << inFile.rdbuf();
	cout << "The first element of the array in the file is defined as the number of elements and is not part of the array" << endl;
	int n;
	mule >> n;
	int* A = new int[n];
	for (i = 0; i < n; ++i) {
		mule >> t;
		A[i] = t;
	}
	if (solution(A, n)) {
		cout << " There is a move that can swap the array back in place" << endl;
	}
	delete[] A;
}
