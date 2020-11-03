#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

bool dfs(int &i, int &j, int &k, int &target, vector<int> &A)
{   
    if((i<=k) && (k<=j))
    {
        if(k == target)
            return true;
            
        else if(A.at(k) != k)
        {   
            return dfs(i,j,A.at(k),target,A);
        }
    }
    return false;   
}

bool bfs(int &i, int &j, int &k, int &sum, vector<int> &A)
{
    if(k > j)
    {
        if (sum != 0) return false;
        else return true;
    }
    
    if((i<=A.at(k)) && (A.at(k)<=j))
    {
        sum -= k;
        ++k;
        return bfs(i, j, k, sum, A);
    }    
    else
    {   
        if((k < j) && (k > i))
        {
            if((j-i) == 1)
                return dfs(i,j,A.at(k+1),k,A) || dfs(i,j,A.at(k-1),k,A);
            
            else if(dfs(i,j,A.at(k+1),k,A) && dfs(i,j,A.at(k-1),k,A))
            {
                sum -= k;
                ++k;
                return bfs(i,j, k, sum, A);  
            }
        }
        else if(k == i)
        {
            if(dfs(i,j,A.at(k+1),k,A))
            {
                sum -= k;
                ++k;
                return bfs(i,j, k, sum, A);  
            }
        }
        else if(k == j)
        {
            if(dfs(i,j,A.at(k-1),k,A))
            {
                sum -= k;
                ++k;
                return bfs(i,j, k, sum, A);  
            }
        }
    }
    return false;
}

int solution(vector<int>& A)
{

    int ans;
    ans = A.size();
    
    for(int i = 0; i <(int)(A.size()-1); i++)
    {
        for(int j = i+1; j < (int)A.size(); j++)
        {
            int sum;
            sum = j*(j+1)/2-i*(i+1)/2+i;
            
            int k;
            k = i;
            
            if(bfs(i, j, k, sum, A))   
                ans++;
        }   
    }
    return ans;
}



int main()
{
    vector<int> A {2,2,4,0,4,0,3,0,1};
    
    cout<<solution(A); 
    
}