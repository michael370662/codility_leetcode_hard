#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <array>
#include <cstring>
using namespace std;

int solution(vector<int> &A, vector<int> &B)
{
    if(A.size() <= 2)
    {
        if((A.size() == 1) || 
        ((A.front() != B.back()) || (B.front() != A.back())) &&
        ((A.front() != A.back()) && (B.front() != B.back())))
            return 1;
        else if(A.size() == 2) return 2;
        else return 0;
    }
    int Amax;
    int Bmax;
    
    Amax = *max_element(A.begin(), A.end()) + 1;
    Bmax = *max_element(B.begin(), B.end()) + 1;
    
    int r[max(Amax,Bmax)];

    int Cindex;
    
    int* Cpointer;
    
    int square;
    
    square = 0;
    
    memset(r, 0, sizeof(r));
    
    for(int i = 0; i < A.size(); i++)
    {
        if(A.at(i) != B.at(i)){
            r[A.at(i)]++;
            r[B.at(i)]++;
        }
        else
        {
            r[A.at(i)]++;
        }
    }

    Cpointer = max_element(r,r + max(Amax,Bmax));
    
    Cindex = distance(r,Cpointer);
    
    return r[Cindex];
}



int main()
{
    vector<int>A{2,3,2,3,5};
    vector<int>B{3,4,2,4,2};
    
    cout << solution(A,B)<<endl;
}
