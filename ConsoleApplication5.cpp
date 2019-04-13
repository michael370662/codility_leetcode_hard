
#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <list>
#include <iterator>
#include <stdexcept>

using namespace std;
/*
*	Zuma game that returns the optimal number of moves to complete a game
*/

class Solution {
public:
	Solution();
	Solution(list<char>& zuma, list<char>& in);
	int findOptPath(list<char>& zuma, list<char>& in, int cnt);
private:
	int cnt;
	bool flag;
};
Solution::Solution() {
	cnt = 0;
	flag = false;
}
Solution::Solution(list<char>& zuma, list<char>& in) {
	cnt = 0;
	cout << "The minimum moves require = (if the number is 2147483647, zuma doesn't have solution)" << endl;
	cout << findOptPath(zuma, in, cnt) << endl;
}
int Solution::findOptPath(list<char>& zuma, list<char>& in, int cnt) {
	int Min = INT_MAX;
	flag = false;
	if (zuma.empty())
		return cnt;
	list<char> ::iterator it;
	list <char> ::iterator tmp;
	it = zuma.begin();
	/*
	*	This part is a terrible implementation of searching for triplets or more and delete. 
	*	In the perfect world, the best way is a DFS kind of search
	*	aka reaches the end and use prev pointer to delete prev to naturally prevent nullptr access at the end
	*	Brute force at it's best or if you like a challenge, this painful approach is singly linked list compatible.
	*/

	while( (it != prev(prev(zuma.end()))) && (it != prev(zuma.end())) && (it != zuma.end())) {
		while ((*it == (*(next(it)))) && (*it == (*next(next(it))))) {
			if (zuma.size() == 3)
				return cnt;
			flag = true;
			tmp = next(it);
			zuma.erase(it);
			it = tmp;
			if (it == prev(prev(zuma.end())))
				break;
		}
		if (flag) {
			tmp = next(it);
			zuma.erase(it);
			it = tmp;
			tmp = next(it);
			zuma.erase(it);
			it = tmp;
			if (zuma.empty())
				return cnt;
			it = zuma.begin();
		}
		if (!flag) {
			++it;
		}
		if (zuma.size() < 3)
			break;
		flag = false;		
	}
	if (zuma.empty())
		return cnt;
	if (in.empty()) {
		return INT_MAX;
	}
	int* func = new int [zuma.size()+1];
	int i;
	i = 0;
	
	/*
	*	The elegant part of this problem is using an array to keep track of all the possible scenarios.
	*	This is one of the shortest way to make use of min_element. This is similar to finding max depth in a tree
	*	Except the tree problem would only require an easy max(param a, param b) implementation. 
	*/
	for (it = zuma.begin(); it != prev(prev(zuma.end())); ++it) {
		char temp = in.front();
		in.pop_front();
		list <char> orig(zuma);
		zuma.insert(it, temp);
		--it;
		cnt++;
		func[i] = findOptPath(zuma, in,cnt);
		cnt--;
		in.push_front(temp);		
		zuma = orig;
		it = zuma.begin();
		for (int j = 0; j < i; ++j) {
			it = next(it);
		}
		++i;		
	}
	int* min = min_element(func,(func + i - 1 ));
	Min = *min;	
	delete[] func;
	return Min;
}


int main()
{
	ifstream inFile;
	inFile.open("Zuma.txt");
	try {
		if (!inFile.is_open())
			throw exception("Check Zuma.txt");
	}
	catch (exception& error) {
		cerr << error.what() << endl;
		return EXIT_FAILURE;
	}
	stringstream mule;
	mule << inFile.rdbuf();
	list <char> zuma(istream_iterator<char>(mule), (istream_iterator<char>()));
	cout << "Input the string you would love to use. End transmission using Ret CtrlZ Ret" << endl;
	list <char> in(istream_iterator<char>(cin), (istream_iterator<char>()));
	Solution(zuma,in);
}

