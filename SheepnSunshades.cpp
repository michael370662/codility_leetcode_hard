#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#define INT_MAX 2147483647


using namespace std;

//The best solution is most likely O(nlogn) using a heap
// Or divide and conquer decribed by wikipedia's cloest pair problem.

int solution(vector<int> &A, vector<int> & B)
{
    int min_S;
    min_S = INT_MAX;
    
    assert(A.size() == B.size());
    
    if(A.size() == 0)
        return -1;
    else if (A.size() == 1)
        return INT_MAX;
    
    for(int i = 0; i < A.size() -1; i++)
    {   
        for(int j = i + 1; j < A.size(); j++)
        {
            if(A[i] == A[j])
                min_S = min(abs(B[j] - B[i]),min_S);
            else if(B[i] == B[j])
                min_S = min(abs(A[j] - A[i]), min_S);
            else
            {
                int maxXY = max(abs(A[j] - A[i]) , abs(B[j] - B[i]));
                min_S = min(maxXY,min_S);
            }
        }
    }
    
    return (min_S / 2);
}
int main()
{
    vector<int> A{0,0,10,10};
    vector<int> B{0,10,0,10};
    cout<<"Expected_5 \t"<<solution(A,B)<<endl;
    vector<int> C{1,1,8};
    vector<int> D{1,6,0};
    cout<<"Expected_2 \t"<<solution(C,D)<<endl;
    vector<int> E{10,20,100};
    vector<int> F{10,20,100};
    cout<<"EXpected_5 \t"<<solution(E,F)<<endl;
    vector<int> G{0,0,0};
    vector<int> H{-10,10,100};
    cout<<"EXpected_10 \t"<<solution(G,H)<<endl;
}
