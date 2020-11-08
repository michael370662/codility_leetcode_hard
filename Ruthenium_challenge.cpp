#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <array>
#include <cstring>
#include <unordered_set>
using namespace std;


int recursion(vector<int>&A, const int K, int* h)
{
    if(K > 1)
        recursion(A, K - 1, h);
    
}

int solution(vector<int> &A, int K)
{
    if(A.size() <= K)
    {
        return A.size();    // Corner case 1, K is more or equals to the amount of elements in the array
    }
    if(A.size() <= 1)
        return A.size();    //Corner case 2, array has no second element for comparision
    //int Amax;
    //Amax = *max_element(A.begin(),A.end()) + 1;  
    
    
    vector<int> B;
    B = A;
    
    unordered_set<int> s;
    for ( auto i : B)
        s.insert(i);
    B.assign( s.begin(), s.end() );
    sort( B.begin(), B.end() ); //sort and remove duplicates in the first vector for the actual list of number needed to be tested.
    
    int h[B.size()];            // array that keep track of the occurence of an int.
    int left[B.size()];	        // left represents current window's starting index
    int count[B.size()];        // stores number of # in current window
	int window[B.size()];       // stores maximum number of continuous #'s found
    int leftIndex[B.size()];    // store left index of maximum window found so far
    
    memset (h, 0, sizeof(h));
    memset (left, 0, sizeof(left));
    memset (count, 0, sizeof(count));
    memset (window, 0, sizeof(window));
    memset (leftIndex, 0, sizeof(leftIndex));

	// maintain a window [left..right] containing at-most k zeroes
	
	
    for(int i = 0; i < B.size(); i++){
    	for (int right = 0; right < A.size(); right++)
    	{
    		// if current element is not #, increase count of # in the
    		// current window by 1
    		if (A.at(right) != B.at(i))
    			count[i]++;
    
    		// window becomes unstable if number of # in it becomes
    		// more than k
    		while (count[i] > K)
    		{
    			// if we have not find #, decrement number of # in the
    			// current window by 1
    			if (A.at(left[i]) != B.at(i))
    				count[i]--;
    
    			// remove elements from the window's left side till window
    			// becomes stable again
    			left[i]++;
    		}
    
    		// when we reach here, the window [left..right] contains at-most
    		// k # and we update max window size and leftmost index
    		// of the window
    		if (right - left[i] + 1 > window[i])
    		{
    			window[i] = right - left[i] + 1;
    			leftIndex[i] = left[i];
    		}
    	}
    }
    int ret = *max_element(window,window + B.size());
    return ret;
}



int main()
{
    vector<int>A{4, 5, 5, 4, 2, 2, 4};
    
    
    cout << solution(A,0)<<endl;
}
