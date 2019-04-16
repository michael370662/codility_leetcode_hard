/*
*	Trapping rainwater
*/
#include "pch.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace std;
class Solution {
public:
	Solution();
	Solution(vector<int>& height);
	int trap(vector<int>& height);
private:
	int sum;
};
Solution::Solution() {
	sum = 0;
}
Solution::Solution(vector<int>& height) {
	sum = 0;
	trap(height);
	cout << "The amt of rainwater is " << sum << endl;
}
int Solution::trap(vector<int>& height) {
	vector<int> ::iterator max;
	vector<int>::iterator previous;
	vector <int> ::iterator it;
	max = max_element(height.begin(), height.end());

	previous = height.begin();
	while (previous != height.end()) {
		if (*previous)
			break;
		previous = next(previous);
	}
	if (next(previous) != height.end()) {
		for (it = next(previous); it != height.end(); ++it) {/*First half of the solution which is technically a palindrome*/
			if ((*previous)) {
				if (*it >= *previous)
				{
					sum += (it - previous - 1)* (*previous);
					previous = it;
				}
				else
					sum -= *it;
			}
			if (it == max)
				break;
		}
	}
	if (max == prev(height.end()))/* Corner case for peak at the end*/
		return sum;
	previous = prev(height.end());
	while (previous != height.begin()) {
		if (*previous)
			break;
		previous = prev(previous);
	}
	if (prev(previous) >= prev(max)) {
		for (it = prev(previous); it != prev(max); --it) {/*Reverse towards the peak*/
			if ((*previous)) {
				if (*it >= *previous)
				{
					sum += (previous - it - 1)* (*previous);
					previous = it;
				}
				else
					sum -= *it;
			}
			if (it == height.begin())/*Corner case for peak at the beginning*/
				break;
		}
	}
	return sum;
}

int main()
{
	ifstream inFile;
	stringstream mule;	
	inFile.open("height.txt");
	try {
		if (!inFile.is_open())
			throw exception("check text file Height");
		mule << inFile.rdbuf();
		vector<int> height((istream_iterator<int>(mule)), istream_iterator<int>());
		Solution::Solution(height);
	}
	catch (exception& error) {
		cerr << error.what() << endl;
		return EXIT_FAILURE;
	}
	
}
