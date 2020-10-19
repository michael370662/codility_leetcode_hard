// you can use includes, for example:
 #include <algorithm>
 #include <numeric>
 #include <cstdlib>
 #include <iostream>
 #include <vector>
 #include <iterator>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
int minimum(std::vector<int> &A, int& i)
{
    if(i < A.size()-1){
        int temp;
        temp = std::abs(std::accumulate(A.end()-i,A.end(),0) - std::accumulate(A.begin(),A.end()-i,0));
            
        return std::min(temp/*std::abs(std::accumulate(A.end()-i,A.end(),0) - std::accumulate(A.begin(),A.end()-i,0))*/,minimum(A,++i));
    }
    
    return std::abs(std::accumulate(A.end()-i,A.end(),0) - std::accumulate(A.begin(),A.end()-i,0));
}

int solution(std::vector<int> &A){
    
    if(A.empty())/* Corner case to prevent A.end()-1 accessing nullptr*/
        return 0;
        
    for(auto it = A.begin(); it != A.end();it++){
        if(*it < 0)
            (*it)*=-1;

    }
    
    if(A.size() == 1)
        return A.front();/*Corner case where A only has 1 element*/
    std::sort(A.begin(),A.end());
    
    int i;
    i = 1;
    
    return minimum(A,i);  
    return -1;/*return error for exception*/
}
    
int main(){
    std::vector<int> A {1, 5 , 2, -2};
    std::cout<<solution(A);
}
