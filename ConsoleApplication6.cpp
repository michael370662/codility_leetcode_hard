/*
*	Return the skyline of a 2 D city given the dimensions of the skyscrapers of the city
*	{{1, 11 ,5},{2, 6 ,7}, {3,13,9}} would ret {{1,11},{3,13},{9,0}}
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>

using namespace std;

class Solution {
public:
	Solution();
	Solution(vector<vector<int>>& bldgs);
	vector<pair<int, int>> getSkyline(vector<vector<int>>& bldgs);
private:
	vector<pair<int, int>> plot;
	int lt;
	int ht;
	int rt;
	int x;
	int y;
};
Solution::Solution() {
	lt = 0;
	ht = 1;
	rt = 2;
	x = 0;
	y = 0;
}
Solution::Solution(vector<vector<int>>& bldgs) {
	lt = 0;
	ht = 1;
	rt = 2;
	x = 0;
	y = 0;
	getSkyline(bldgs);
	for (int i = 0; i < plot.size(); i++) {
		cout << get<0>(plot[i]) << ", " << get<1>(plot[i]) << endl;
	}
}

vector<pair<int, int>> Solution::getSkyline(vector<vector<int>>& bldgs) {
	vector<vector <int>> :: iterator its;
	vector<vector <int>> ::iterator prev;
	prev = bldgs.begin();
	plot.emplace_back(make_pair(prev->at(lt), prev->at(ht)));
	if (next(bldgs.begin()) == bldgs.end()) {
		plot.emplace_back(make_pair(prev->at(rt), 0));
	}

	for (its = next(bldgs.begin()); its != bldgs.end(); ++its) {
		if (its->at(lt) < prev->at(rt)) {
			if (its->at(ht) >= prev->at(ht)) {
				plot.emplace_back(make_pair(its->at(lt), its->at(ht)));
				prev = its;
			}			
			else {/* The second skyscraper is not as tall as the 1st and it ends before the 1st*/
				if (its->at(rt) <= prev->at(rt))
					bldgs.erase(its);
				else
					its->at(lt) = prev->at(rt);
				sort(bldgs.begin(), bldgs.end());
				its = prev;
			}
		}
		else if (its->at(lt) == prev->at(rt)) {
			plot.emplace_back(make_pair(its->at(lt), its->at(ht)));
			prev = its;
		}
		else/* The 1st skyscraper ends before the second comes in */ {
			plot.emplace_back(make_pair(prev->at(rt), 0));
			plot.emplace_back(make_pair(its->at(lt), its->at(ht)));
			prev = its;
		}
	}
	plot.emplace_back(make_pair(prev->at(rt), 0));
	return plot;
}


int main()
{
	ifstream inFile;
	int mule;
	inFile.open("skyscraper.txt");
	try {
		if (!inFile.is_open())
			throw exception("skyscraper.txt is not available");
	}
	catch (exception& error) {
		cerr << error.what() << endl;
		return EXIT_FAILURE;
	}
	
	vector<vector<int>> bldgs;
	vector<int> bldg;	

	try {/*Avoid crashing program prematurely with NULL access that could happen with user I/P*/
		while (inFile) {
			for (int i = 0; i < 3; ++i) {
				inFile >> mule;
				bldg.emplace_back(mule);
			}
			bldgs.emplace_back(bldg);
			bldg.clear();
			if (inFile.eof()) {
				Solution::Solution(bldgs);
				break;				
			}
		}
		//Solution(bldgs);
	}
	catch (exception& error) {
		cerr << error.what() << endl;
		return EXIT_FAILURE;
	}
}
