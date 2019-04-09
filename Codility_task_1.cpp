#include "pch.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <numeric>
/*
*Design a program that find the index at which the sum before the index and the sum after
*equates. 
*/

using namespace std;

int solution(vector<int>& A) {
	int p;
	p = -1;
	if (accumulate(A.begin()+1, A.end(), 0) == A.at(0))
		return 0;
	else if (accumulate(A.begin(), A.end()-1, 0) == A.at(A.size()-1))
		return (A.size() - 1);
	else for (p = 1; p < A.size() - 1; ++p) {
		/*Since the ending index of accumulate exclude the index itself, we put p instead of p - 1*/
		if (accumulate(A.begin(), (A.begin() + int(p)), 0) == accumulate(A.begin() + int(p + 1), A.end(), 0))
			return p;	
	}
	return -1;
		
};

int main()
{
	stringstream mule;
	ifstream inFile;
	inFile.open("numbers.txt");
	try {
		if (!inFile.is_open())
			throw exception("The File cannot be opened");
		mule << inFile.rdbuf();
	}
	catch(const exception& error){
		cerr<< error.what()<<endl;
		return (EXIT_FAILURE);
	}
	vector<int> a((istream_iterator<int>(mule)),(istream_iterator<int>()));
	/*Check if it is a file with only numbers*/

	try {
		copy((istream_iterator<int>(mule)), istream_iterator<int>(), back_inserter(a));
	}
	catch (const exception& error) {
		cerr << error.what() << endl;
		return(EXIT_FAILURE);
	}
	cout << "The index that divide 2 equal sum in an array is (0-indexed) ";
	if (solution(a)) {
		cout << solution(a) << endl;
	}
	else
		cout << "not there" << endl;
	return 0;
}
