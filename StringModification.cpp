#include <iostream>
#include <vector>

using namespace std;

int solution(string& S, int k) {
    
    // Sting > k
    if(k > S.size()) 
    {
        cerr << "String is shorter than requested length."<<endl; 
        exit(0);
    }
    
    // init count for sliding window
    bool flag = false;
    int ret_val = 0;
    int cnt = 0;
    for(int i = 0; i < S.size(); i++) {
        if(S[i] == 'M') cnt++;
        else cnt = 0;
        if(cnt == k) flag = true;
        if(cnt > k) S[i] = 'L', ret_val++, cnt = 0;
    }
    if(flag || (k == 0)) return ret_val;
    // Sliding window
    cnt = 0;
    for(int i=0; i < k; i++) {
        if(S[i] == 'L') cnt++;
    }
    ret_val = cnt + (S[k] == 'M');
    int revert_M = 0; 
    for(int i=k; i<S.size(); i++) {
        if(S[i-k] == 'L') cnt--;
        if(S[i] == 'L') cnt++;
        revert_M = 0;
        
        if(S[i-k] == 'M')
                revert_M++;
        if(i < S.size()-1 && S[i+1] == 'M')
            revert_M++;
            
        if(S[i-k] == 'M' && S[i] == 'M')
            revert_M++;
        ret_val = min(ret_val, cnt + revert_M);
    }
    return ret_val;
}

int main() {

    string S{"MLM"};
    string A{"MLMMLLM"};
    string B{"MLMMMLMMMM"};
    int k;
    k = 2;
    cout << solution(S, k) << endl;
    cout << solution(B,k) <<endl;// expected 
    return 0;
}