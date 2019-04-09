#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
/*
* Leetcode question that test on for matches on strings provided with only once in occurence.
* Return the indexes of the first occurence of such matching patterns
* Once in occurence is understood as this if foobarpppppbarfoo is the given
* foo bar would return 0 and 12 foobar as 1 hit and barfoo as second hit; f as first index and b as 2nd index
* foo would return 0 and 15
*/


using namespace std;

template<typename A, typename B>
pair<B, A> flip_pair(const pair<A, B> &p)
{
	return pair<B, A>(p.second, p.first);
}
template <typename A, typename B>
multimap<B, A> flip_map(const map<A, B> &src)
{
	multimap<B, A> dst;
	transform(src.begin(), src.end(), inserter(dst, dst.begin()), flip_pair<A, B>);
	return dst;
}


class Solution {
public:
	Solution(string s, vector<string>& words);
	vector <int> findSubstring(string s, vector<string>& words);
	int findSubstringUtil(string s, vector <string>& words, vector<int>& index, map<string, int> M, size_t pos);

};
Solution::Solution(string s, vector<string>& words) {
	findSubstring(s, words);
}

int Solution::findSubstringUtil(string s, vector <string>& words,vector<int>& index, map<string, int> M, size_t pos) {
	size_t hit = 0;
	size_t length = 0;
	for (int i = 0; i < words.size(); ++i) {
		
			hit = s.find_first_of(words.at(i), pos);
			if (hit == string::npos) {
				M.clear();
				return 0;
			}
			M[words.at(i)] += hit;	
		}
	multimap <int, string> dst = flip_map(M);
	multimap<int, string>::iterator it;
	for (it = dst.begin(); it!= prev(dst.end()); ++it) {
		length = it->second.size();
		if (length + it->first != next(it)->first) {
			M.clear();
			dst.clear();
			return 0;
		};
	}
	/*Store away substring for recursive comparison*/
	pos = it->first + it->second.size();
	index.emplace_back(dst.begin()->first);	
	M.clear();
	dst.clear();
	if (pos != s.size()) {/*Recursion iff not end*/
		findSubstringUtil(s, words, index, M,  pos);
	}
	return 1;
};

vector <int> Solution::findSubstring(string s, vector<string>& words) {
	map <string,int> M;
	vector<int> index;
	size_t pos = 0;
	findSubstringUtil(s,words,index,M, pos);
	if (index.empty()) {
		cout << "No index matches description" << endl;
		return index;
	}
	cout << "The index found are as follow" << endl;
	vector<int>::iterator it;
	for (it = index.begin(); it != index.end();++it) {
		cout << "\t" <<*it << endl;
	}
	return index;
}


int main()
{
	ifstream inFile;
	stringstream mule;
	string S;
	inFile.open("String.txt");
	try {
		if (!inFile.is_open())
			throw exception("File cannot be opened");
	}
	catch (exception& error) {
		cerr << error.what() << endl;
		return EXIT_FAILURE;
	}
	mule << inFile.rdbuf();
	S = mule.str();
	cout << "Please input desired word combos seperated by space " << endl;
	cout << "Press RET Ctrl - Z RET to confirm transmission" << endl;
	vector<string> words(istream_iterator<string>(cin), (istream_iterator<string>()));	
	if (S.empty()) {
		cout << "Please check string.txt and provide a valid string" << endl;
		return -1;
	}
	if (words.empty()) {
		cout << "Please input a valid string for comparison" << endl;
		return -1;
	}
	Solution(S, words);	
}
