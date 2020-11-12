#include <vector>
#include <iostream>
#include <numeric>
#include <cstring>
#include <cmath>
#include <algorithm>


unsigned long mask2(unsigned param)
{
    static const unsigned long masks[] = {
        0x00000000UL, 0x00000001UL, 0x00000003UL, 0x00000007UL,
        0x0000000fUL, 0x0000001fUL, 0x0000003fUL, 0x0000007fUL,
        0x000000ffUL, 0x000001ffUL, 0x000003ffUL, 0x000007ffUL,
        0x00000fffUL, 0x00001fffUL, 0x00003fffUL, 0x00007fffUL,
        0x0000ffffUL, 0x0001ffffUL, 0x0003ffffUL, 0x0007ffffUL,
        0x000fffffUL, 0x001fffffUL, 0x003fffffUL, 0x007fffffUL,
        0x00ffffffUL, 0x01ffffffUL, 0x03ffffffUL, 0x07ffffffUL,
        0x0fffffffUL, 0x1fffffffUL, 0x3fffffffUL, 0x7fffffffUL,
        0xffffffffUL };

    if (param < (sizeof masks / sizeof masks[0]))
        return masks[param];
    else
        return 0xffffffffUL; /* More than 32 bit */
}

using namespace std;
int solution(vector<vector<int>> &A)
{
    // select bitmask
    unsigned long bitmask;
    int n = A[0].size();
    
    bitmask = mask2(n);
    
    int size = pow(2,n);	 
    
    unsigned int count[size];
    memset(count,0,sizeof(count));
    
    for(int i = 0; i < A.size(); i++)
    {
	    unsigned int number = 0;
        for(int j = 0; j < n; j++)
            number = ((A[i][j] << n-j-1) | number); //set j bit
	    count[number]++;
	    count[(number^bitmask)]++;
	    //  Since the complement of a number is also the answer, this would save on runtime.
    }
    
    
    return *max_element(count,count+size);
}

int main()
{
    vector<vector<int>> A
    {
        {0,0,0,0},
        {0,1,0,0},
        {1,0,1,1}
    };
    
    cout<<solution(A)<<endl;
    
    vector<vector<int>> B
    {
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1},
        {1,0,1,0}
    };
    
    cout<<solution(B)<<endl;
    
    
    vector<vector<int>>C
    {
        {1},
        {0},
        {1},
        {1},
        {1},
        {0},
        {1},
        {1},
        {0},
    };
    cout<<solution(C)<<endl;
}

void print(vector<vector<int>> &A)
{
    for (int i = 0; i < A.size(); ++i)
    {
        for (int j = 0; j < A[0].size(); ++j)
            cout<<A[i][j];
        cout<<endl;
    }   
}