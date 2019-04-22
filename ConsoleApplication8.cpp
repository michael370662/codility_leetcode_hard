/*
*	Alien Dictionary leetcode. There's an alien language which uses litin alphabet
*	w/ different order.  Derive word order given that the I/P is sorted lexicographically
*/
#include "pch.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

class Solution{
public:
	Solution() {};
	Solution(vector<string>& words);
	string alienOrder(vector<string>& words);
private:
	string ans;
	char ch;
};

Solution::Solution(vector<string>& words) {
	cout << "The order of words is as follow" << endl;
	cout << alienOrder(words)<< endl;
}

string Solution :: alienOrder(vector<string>& words) {
	if (words.empty())
		return " ";
	unordered_map<char, int> indegree;
	unordered_map<char, multiset<char>> hash;
	vector<string> :: iterator itw;	
	string::iterator itc;
	
	for (itw = words.begin(); itw != words.end(); ++itw)
		for (itc = ((*itw).begin()); itc != ((*itw).end()); ++itc)
			indegree[*itc] = 0;
	for (int i = 1; i < words.size(); ++i) {
		for (int j = 0; j <= min(words.at(i - 1).size(), words.at(i).size()); ++j) {
			if (words.at(i - 1).at(j) != words.at(i).at(j)) {
				indegree[words.at(i).at(j)]++;
				hash[words.at(i - 1).at(j)].insert(words.at(i).at(j));
				break;
			}
		}
	}
	unordered_map<char, int> :: iterator ii;	
	unordered_map<char, int> ::iterator ij;
	multiset<char> :: iterator ih;
	for (ij = indegree.begin(); ij != indegree.end(); ++ij) {
		for (ii = indegree.begin(); ii != indegree.end(); ++ii) {
			if (!(ii->second)) {
				ans += ii->first;
				if (hash.find(ii->first) != hash.end()) {
					for (ih = hash.at(ii->first).begin(); ih != hash.at(ii->first).end(); ++ih) {
						indegree[*ih]--;
					}
				}
				ii->second--;
			}
			
		}	
		if (ans.empty())
			return " ";
	}
	return ans;
}

using namespace std;
int main()
{
	ifstream inFile;
	stringstream stream;
	inFile.open("dictionary.txt");
	try {
		if (!inFile.is_open())
			throw exception("chk dictionary txt file");
		stream << inFile.rdbuf();
		vector<string>words(istream_iterator<string>(stream), (istream_iterator<string>()));
		Solution::Solution(words);
	}
	catch (exception& error) {
		cerr << error.what() << endl;
	}
    
}

