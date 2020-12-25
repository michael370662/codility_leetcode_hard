/*
** This is probably the most elegant solution on the
** entire internet now. Only 3 lines of constructive
** code. 100% solution
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int solution(int N, int M, vector<int> &X, vector<int> &Y)
{
    int ret_val = 0;
    
    const int half = X.size()/2;
    if(X.size() % 2){
        return 0;
    }
    //The following 3 lines solve the problem above deals
    //with exception cases.
    sort(X.begin(),X.end());
    sort(Y.begin(), Y.end());
    
    ret_val = X[half] - X[half-1] + Y[half] -Y[half-1];


    return ret_val;
}
int main() {
    
    int N = 4;
    int M = 1;

    vector<int> X{3,1};
    vector<int> Y{0,0};
    cout << solution(N,M,X,Y) << endl; //expected 2
    return 0;
}