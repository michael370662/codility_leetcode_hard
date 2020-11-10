//https://www.geeksforgeeks.org/internal-working-of-hashmap-java/
//https://brilliant.org/wiki/sorting-algorithms/
//Study these 2

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstring>
#include <algorithm>

using namespace std;

vector<int> solution(int K, int M, vector<int> &A)
{
    vector<int> ret;     //store left index of maximum window found so far
    	       
    int count[M + 2];        // stores number of # in current window
	
	int addcount;        // count number of adds performed.
	
	addcount = 0;
	
	int threshold;
	threshold = A.size()/2;
	
    memset (count, 0, sizeof(count));

	// maintain a window [left..right] containing at-most k zeroes
	
	for(int i = 0; i < A.size() ; i++){count[A.at(i)]++;}   // init count before AddOP;
	    
	for(int i = 0; i < A.size() - K; i++)
	{
	    int j = i;
        while(addcount < K)
        {
            count[A.at(i)]--;
            A.at(i)++;
            count[A.at(i)]++;
            i++;
            addcount ++;
        }
        if (count[A.at(i)] > threshold)//The number sliding in is majority
        {
            ret.push_back(A.at(i));
        }
        
        if (count[A.at(j)] > threshold)//The # sliding out is majority
        {
            ret.push_back(A.at(j));
        }
        
        //window moved to the right, the Add1 OP reverted.
        while(0 < addcount)
        {   
            --i;
            count [A.at(i)]--;
            A.at(i)--;
            addcount --;
            count[A.at(i)]++;
        }
    }
    int i = A.size() - K; 
    while(addcount < K)
    {
        count[A.at(i)]--;
        A.at(i)++;
        count[A.at(i)]++;
        i++;
        addcount ++;
    }
    
    for(int i = A.size() - 1; i > -1; i--)
    {
        if (count[A.at(i)] > threshold)//is majority
        {
            ret.push_back(A.at(i));
        }
    }
    
    unordered_set<int> s;   //Method to toss out the duplicate
    for ( auto i : ret)
        s.insert(i);
    ret.assign( s.begin(), s.end() );
    
    sort(ret.begin(),ret.end());
    
    return ret;
}


int main()
{
    vector<int>A {2,1,3,1,2,2,3};
    
    for(auto vIt : solution(3,5,A))
    {
        cout<<vIt<<endl;
    }
}