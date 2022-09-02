#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
    vector<vector<int>> myGrid; //local copy of the grid
    int dp[50][50][50]; //confinement constraints
    int dfs(int r1,int c1,int r2,int N){
        int c2 = r1+c1-r2; //symmetrical distance, r1+c1  c1+r2
        if((r1>N)||(r2>N)||(c1>N)||(c2>N)) //Deny out of bound access
            return INT_MIN;
        else if((myGrid[r1][c1] == -1)||(myGrid[r2][c2] == -1)) //Forbidden grid
            return INT_MIN;
            
        if((r1==N)&&(c1==N)) return myGrid[r1][c1]; //Recursion ends at bottom right corner
        if(dp[r1][c1][r2] != -1) return dp[r1][c1][r2]; //If path was traversed
        
        //Cherry can be only picked up once on same grid
        int current = (c1 == c2)? myGrid[r1][c1]:(myGrid[r1][c1] + myGrid[r2][c2]); 
        
        int leafGrids = max(dfs(r1+1,c1,r2,N),dfs(r1,c1+1,r2,N));
        leafGrids = max(leafGrids,dfs(r1+1,c1,r2+1,N));
        leafGrids = max(leafGrids,dfs(r1,c1+1,r2+1,N));
        current += leafGrids;
        
        dp[r1][c1][r2] = current;//Memorization for better time complexity
        return current;
    }
    public:
    
    int cherryPickup(vector<vector<int>>& grid){
        int n = grid[0].size();
        memset(dp,-1,sizeof dp);
        myGrid = grid;
        return max(0,dfs(0,0,0,n-1));
    }
};
int main(){
    vector<vector<int>> grid = {{0,1,-1},{1,0,-1},{1,1,1}};
    Solution solution;
    cout<<solution.cherryPickup(grid)<<endl;
    return 0;
}
