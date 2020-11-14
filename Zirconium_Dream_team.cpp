#include <vector>
#include <algorithm>
#include <unordered_set>
#include <numeric>
#include <iostream>
#include <cassert>

#define INT_MIN    -2147483648

using namespace std;
int solution(vector<int> &A, vector<int> &B, int K)
{
    if(A.size() == 0)
        return 0;
    else if (A.size() == 1)
        return A.at(0) + B.at(0);   //2 Corner cases when the size of vector doesn't require picking.
	if(K == A.size())
	    return accumulate(A.begin(),A.end(),0);
	else if(K == 0)
	    return accumulate(B.begin(),B.end(),0);
	int array[K];   //Store unique index
	fill(array, array + K, -1);
	    
	assert(A.size() == B.size());

    vector<int> C;
    C.reserve(A.size());

    std::transform(A.begin(), A.end(), B.begin(), 
                   std::back_inserter(C), minus<int>());
    for(int i = 0; i < K; i++)
    {
        vector<int> :: iterator pointer = max_element(C.begin(), C.end());
        array[i] = distance(C.begin(),pointer); //
        *pointer = INT_MIN;    // Set value to minimum to avoid retracing here.
    }
    int sum;
    sum = 0;
    sum += accumulate(B.begin(),B.end(), 0);
    for(int i = 0; i < K; i++)
    {
        sum += A.at(array[i]);
        sum -= B.at(array[i]);
    }
    
    //  Since the complement of a number is also the answer, this would save on runtime.
    return sum;
    
}

int main()
{
    vector<int> A{4,2,1};
    vector<int> B{2,5,3};
    vector<int> C{7,1,1,4};
    vector<int> D{5,3,4,3};
    vector<int> E{5,5,5};
    vector<int> F{5,5,5};
    
    cout<<"max_Contribution_10"<<solution(A,B,2)<<"\t"<<"max_Contribution_18"<<solution(C,D,2)<<"\t"<<"max_Contribution_15"<<solution(E,F,1)<<"\t"<<endl;
}
