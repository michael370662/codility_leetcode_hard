#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
       auto lengthOfString = s.length();
       for(vector<string>::iterator i = wordDict.begin(); i != wordDict.end(); i++){
        auto pos = s.find(*i);
        if (pos != string::npos) {
            auto lengthOfWord = i->length();
            s.erase(pos, lengthOfWord);
            if(s.empty())
                return true;
            wordBreak(s, wordDict);
        }
       }
       return false;
    }
};
int main() {
    string s("aaaaaaa");
    string one("aaaa");
    string two("aaa");
    vector<string>wordDict;
    wordDict.push_back(one);
    wordDict.push_back(two);
    
    Solution solution;
    bool flag = solution.wordBreak(s,wordDict);
    cout<<flag<<endl;
    return 0;
}
