#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>

/*
* Leetcode task that asked for the ret of median of two sorted array when combined.
* Specs: O/P the avg of the median when the total amount of combined elements in even.
* Else just ret the one single elements.
* Potential problem: declare float on the ret values as to prevent ret of int when a median such as 2.5 is 
* ret.
*/
using namespace std;

class Solution {
public:
	Solution();
	/*~Solution()*/
	Solution(vector<int>& Nums1, vector<int>& Nums2);
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
private:
	vector<int> nums1;
	vector<int> nums2;
	vector<int> dst;
	int elements;
};

Solution::Solution(){/*Constructor*/
	nums1.reserve(0);
	nums2.reserve(0);
	dst.reserve(0);
	elements = 0;
}
Solution::Solution(vector<int>& Nums1, vector<int>& Nums2){/*Constructor*/
	nums1 = Nums1;
	nums2 = Nums2;
	elements = 0;
	cout << "The median of the two combined array is " << findMedianSortedArrays(nums1, nums2) <<endl;
}
double Solution::findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2){
	/*MergeSort*/
	sort(nums1.begin(),nums1.end());
	sort(nums2.begin(),nums2.end());
	merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), back_inserter(dst));
	/*Handle odd or even*/

	elements = dst.size();
	switch (elements % 2) {
		/*dst would not have no element because such condition is checked and handled in main function*/
		/*Here there's a need to amend this program to handle potential float values*/
	case 0: {/*Even*/
		return (dst.at(elements / 2) + dst.at(elements / 2 + 1)) / 2;
		break;
	}
	default: {/*Odd*/
		return dst.at(elements / 2);
		break;
	}
	}
}

int main()
{
	stringstream inums1;
	stringstream inums2;
	ifstream inFile1;
	ifstream inFile2;
	try {

		inFile1.open("nums1.txt");
		inFile2.open("nums2.txt");
		{
			/* Make sure we have something to read */
			if (!inFile1.is_open()) {
				throw exception ("Could not open nums1.txt");
			}
			if (!inFile2.is_open()) {
				throw exception ("Could not open nums2.txt");
			}
			/* Copy contents as efficiently as possible */
			inums1 <<inFile1.rdbuf();
			inums2 << inFile2.rdbuf();
		}

	}
	catch (const exception& error) {
		cerr << error.what() << endl;
		return(EXIT_FAILURE);

	}

	vector<int> nums1((istream_iterator<int>(inums1)), istream_iterator<int>());
	vector<int> nums2((istream_iterator<int>(inums2)), istream_iterator<int>());
	/*Check if it is a file with only numbers*/
	try {
			copy(istream_iterator<int>(inums1), istream_iterator<int>(), back_inserter(nums1));
			copy(istream_iterator<int>(inums2), istream_iterator<int>(), back_inserter(nums2));
	}
	catch (const exception& error) {
			cerr << error.what() << endl;
			return(EXIT_FAILURE);
	}
	Solution(nums1,nums2);
	return 0;
}