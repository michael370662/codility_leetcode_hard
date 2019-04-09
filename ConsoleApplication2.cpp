#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>

/*
* Leetcode problem that asked for the comparison of two strings. Return true if both strings matches
* '.' Being the universal joker while '*' being a flexible multiplier of char from 0 to infinity
* ".*" is universal true as it stands for infinite joker towards any string
* "abdec" of course matches I/P "abdec
* It also matches with "p*b*abdech*o*" Here * is a 0 multiplier that negates all wrong chars
* It also matches with "a*b*d*f*abdec" Here * negates a, b, d and f because f breaks the sequence for it to be true.
* It also matches with "ab..c" Here universal is used
* it also matches with "ab..c*" Here * is used as 1 multiplier that keeps c in position.
*/

using namespace std;

class Solution {
public:
	/*~Solution()*/
	Solution(string S, string P);
	bool isMatch(string s, string p);

private:
	string s;
	string p;
	char last;
};

Solution::Solution(string S, string P) {
	string s(S);
	string p(P);
	last = '~';
	(isMatch(s, p)? cout<<"Matches"<<endl : cout<<"Try again"<<endl );
}
bool Solution::isMatch(string s, string p) {
	string::iterator its = s.begin();
	string::iterator itp = p.begin();
	string rs(s.begin() + 1, (s.end()));
	string rp(p.begin() + 1, (p.end()));
	switch ((((*its == *itp) || (*itp == '.'))<<1) + (*itp == '*')) {
	case 0: {/*Current mismatch*/
		last = *itp;
		switch ((((its + 1) == s.end()) << 1) + ((itp + 1) == p.end())) {
		case 0: {
			if (*(itp + 1) == '*') {
				return ((isMatch(rs, rp)) || isMatch(s, rp) || isMatch(rs, p));
			}
			else
				return false;
			break;
		}
		case 1: {
			return false;
			break;
		}
		case 2: {
			if (*(itp + 1) == '*') {
				return (isMatch(s, rp));
			}
			else 
				return false;
			break;
		}
		case 3: {
			return false;
			break;
		}
		default:
			return true;
			break;
		}
		break;
	}
	/*Case 3 is impossible*/
	case 1: {
		switch ((((its + 1) == s.end()) << 1) + ((itp + 1) == p.end())) {
		case 0: {
			return ((isMatch(rs, rp)) || isMatch(s, rp) || isMatch(rs, p));
			break;
		}
		case 1: {
			if ((*its == last) || (last == '.')) {
				return (isMatch(rs, p));
			}
			else
				return false;
			break;
		}
		case 2: {
			if ((*(itp + 1) != '*') && (itp + 2 != p.end())) {
				string rp(p.begin() + 2, (p.end()));
				return (isMatch(s, rp));
			}
			else 
				return (isMatch(s, rp));
			break;
		}
		case 3: {
			if ((*its == last) || (last == '.'))
				return true;
			else
				return false;
			break;
		}
		default:
			return true;
			break;
		}
		break;
	}
	case 2: {
		last = *itp;
		switch ((((its + 1) == s.end())<<1) + ((itp + 1) == p.end())) {
		case 0: {
			if (*(itp + 1) == '*') {
				return ((isMatch(rs, rp)) || isMatch(s, rp) || isMatch(rs, p));
			}
			else
				return ((isMatch(rs, rp)) || isMatch(s, rp));
			break;
		}
		case 1: {
			return false;
			break;
		}
		case 2: {
			if ((*(itp + 1) != '*') && (itp + 2 != p.end())) {
				string rp(p.begin() + 2, (p.end()));
				return (isMatch(s, rp));
			}
			else
				return (isMatch(s, rp));
			break;
		}
		case 3: {
			return true;
			break;
		}
		default:
			return true;
			break;			
		}		
		break;
	}
	default: {
		return false;
	}
	}
}

int main() {
	ifstream inFile;
	try {
		inFile.open("strings.txt");
		{
			if (!inFile.is_open())
				throw exception("Cannot open the file with strings");
		}		
	}
	catch(const exception& error){
		cerr << error.what() << endl;
		return(EXIT_FAILURE);
	}
	string S(istream_iterator<char>(inFile), (istream_iterator<char>()));
	cout << "Please provide a pattern desired below, to end transmission press ENTER + CTRL-Z + ENTER" << endl;
	string P(istream_iterator<char>(cin), (istream_iterator<char>()));
	if (S.empty()) {
		cout << "Please check string.txt and provide a valid string" << endl;
		return -1;
	}
	if (P.empty()) {
		cout << "Please input a valid string for comparison" << endl;
			return -1;
	}
	Solution(S, P);
	return 0;
}
	
