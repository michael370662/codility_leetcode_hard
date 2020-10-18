// you can use includes, for example:
 #include <algorithm>
 #include <numeric>
 #include <cstdlib>
 #include <iostream>
 #include <vector>
 #include <iterator>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
int solution(std::vector<int> &A){
    
    if(A.empty())/* Corner case to prevent A.end() accessing nullptr*/
        return -1;
    
    for(auto it = A.begin(); it != A.end();it++){
        if(*it < 0)
            (*it)*=-1;

    }
    std::sort(A.begin(),A.end());
    return A.back()-std::accumulate(A.begin(),A.end()-1,0);  
    return -1;
}
int main(){
    std::vector<int> A {1, 5 , 2, -2};
    std::cout<<solution(A);
}
