/*  Brute force solution that fails perfomance test and huge string
**  1.Permute all possible combinations of all lengths i.e. {a,b,c} =
**  {a},{b},{c},{a,b},{a,c},{b,c},{b,a},{c,a},{c,b},{a,b,c},{a,c,b},
**  {b,c,a},{c,b,a},{c,a,b},{b,a,c}
**  2.Use sliding Window to isolate permutations of different length
**  3.ChkPalindrome and return positive results.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

bool chkPalindrome(vector<string> &A)
{
    string str;
    for (int i = 0; i < A.size(); i++)
    {
        str.append(A[i]);
    }
    int l = 0;
    int r = str.length() - 1;
    while(r>=l)
    {
        if (str[l] != str[r])
        {
            return false;
        }
        ++l;
        --r;
    }
    return true;
}
string slidingWindow(vector <string>& A)// Default set at k >= 1
{
    for(int k = 1; k < A.size();k++)
    {
        int l = 0;
        int r = k;
        for(;r <= A.size();r++, l++)
        {
            vector<string> B;
            copy(A.begin() + l, A.begin() + r, back_inserter(B));
            
            if(chkPalindrome(B))
            {
                string retString;
                for (int i = 0; i < B.size(); i++)
                {
                    retString.append(B[i]);
                    retString +=' ';
                }
                retString = retString.substr(0, retString.length() - 1);
                return retString;
            }
        }
        
    }
    //default case operate with entire string
    if(chkPalindrome(A))
    {
        string retString;
        for (int i = 0; i < A.size(); i++)
        {
            retString.append(A[i]);
            retString +=' ';
        }
        retString = retString.substr(0, retString.length() - 1);
        return retString;
    }
    else return "NO";
}

string permute(vector<string>& A, int l, int r)
{
    string retString;
    retString = "NO";
    if(l == r)
    {
        retString = slidingWindow(A);
    }
    else 
    {
        for(int i = l; i <= r; i++)
        {
            swap(A[l], A[i]);
            retString = permute(A, l+1 ,r );
            if(retString != "NO")
                return retString;
            swap(A[l],A[i]);
        }
        
    }
}
string solution(string &str)
{
    vector<string> A;
    for(string::iterator sIt = str.begin(); sIt != str.end(); sIt++)
    {
        string temp;
        while((static_cast<char>(*sIt) != ' ') && (sIt != str.end()))
        {
            temp += *sIt;
            ++sIt;    
        }
        A.push_back(temp);
        if(sIt == str.end())
            break;
    }
    return permute(A, 0, A.size()-1);
}

int main()
{
    string str{"by metal owl egg mr crow worm my ate"};
    string str1{"mr owl ate my metal worm"};
    string str2{"abcc bc ac"};
    string str3{"live on time emit no evil"};
    cout<<solution(str)<<endl;
    
    return 0;
}
