// you can use includes, for example:
 #include <algorithm>
 #include <numeric>
 #include <cstdlib>
 #include <iostream>
 #include <vector>
 #include <iterator>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;
int min_banner(std::vector<int> &A, int& i)
{
    int product1;
    int product2;
    int sum;
    
    product1 = 0;
    product2 = 0;
    sum = 0;
    
    int max1;
    int max2;
    
    max1 = 0;
    max2 = 0;
    
    if(i < A.size()-1)
    {
        max1 = std::distance(A.begin(),std::max_element(A.begin(),A.begin()+i+1));
        max2 = std::distance(A.begin(),std::max_element(A.begin()+1+i, A.end()));
        
        product1 = (A.at(max1))*(i+1);	//size of banner1
        product2 = (A.at(max2))*(A.size()-i-1);	//size of banner2
        
        sum = product1 + product2;
        
        return std::min(sum, min_banner(A,++i));
        
    }
    
    max1 = std::distance(A.begin(),std::max_element(A.begin(),A.end()));	// corner case with 1 giant banner
    sum = (A.at(max1))*(A.size());
    
    return sum;
}

int solution(std::vector<int> &A){
    int i;	// used as an iterator to traverse through the bldgs
    i = 0;
    return min_banner(A,i); 
}
    
int main(){
    std::vector<int> A {1, 5 , 2, 2};
    std::cout<<solution(A);
}
