#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <utility>
#include <iterator>

using namespace std;


int parse_map(multimap<int,tuple<char,bool,int>>& record, char& c, multimap<int,tuple<char,bool,int>> :: iterator &mIt)
{ 
    int idx = -1;
    int retval = 0;
    bool notFound = false;
    
    
    if((get<bool>(mIt->second)) && mIt->first > 0)
    {
        retval +=mIt->first;
        if(mIt != record.begin())
            --mIt;
        else
            return retval;
        
        for(;mIt->first > 0; mIt-- )
        {
            if(get<char>(mIt->second) == c)
            {
                retval += mIt->first;
                break;
            }
            if(mIt == record.begin())
                break;
        }
        notFound = true;
    }
    else if(mIt->first > 0)
    {
        retval += mIt->first;
        idx = get<int>(mIt->second);
        for(;mIt->first > 0; mIt--)
        {
            if((get<bool>(mIt->second)) && (get<char>(mIt->second) == c))
            {
                retval += mIt->first;
                break;
            }
        }
        notFound = true;   
    }
    if(mIt->first > 0 || notFound) 
        mIt = record.begin();
    else 
    {
        retval -= mIt->first;
        auto mIte = record.end();
        --mIte;
        while((get<char>(mIte->second) != c) && (mIte->first > 0))
        {
            --mIte;
        }
        if(mIte->first > 0)
        {
            if(get<int>(mIte->second) != get<int>(mIt->second))
            {    
                retval = parse_map(record,c,mIte);
            }
            else
            {
                --mIte;
                if(mIte->first > 0)
                    retval = parse_map(record,c,mIte);
            }
        }
        return retval;
    }
    for(;mIt->first < 0; mIt++)
    {   
        //Prefix scenario
        if ((get<int>(mIt->second) != idx) && (get<char>(mIt->second) == c))
        {
            retval -= mIt->first;
            break;
        }
    }
    return retval;
}
int solution(vector<string> &A)
{
    int max_substring;
    max_substring = 0;
    int substring_idx = -1;
    multimap<int,tuple<char,bool,int>> record;
    for(int i = 0; i < A.size(); i++)
    {
        int count;
        count = 1;
        // 2 Corner cases, 1 empty and the other only has 1 char
        if(A[i].size() == 0)
            continue;
        else if(A[i].size() == 1)
        {
            tuple<char,bool,int> p = make_tuple(A[i].front(), true,i);
            multimap<int,tuple<char,bool,int>> :: iterator mIta;
            for(mIta = record.begin(); mIta != record.end(); mIta++)
            {
                if ((get<char>(mIta->second) == get<char>(p)) && get<bool>(mIta->second))
                    break;
            }
            if(mIta != record.end())
            {
                record.insert({count + mIta->first,p});
                record.erase(mIta);
            }
            else
            {
                record.insert({count,p});
            }
            continue;
        }
        
        for(int j = 1; j < A[i].size(); j++)
        {
            if (A[i][j] == A[i].front())
            {
                count ++;
            }
            else 
            {
                for(int g = A[i].size() -2; g > j; g--)
                {
                    char temp = A[i][g];
                    int len = 1;
                    while((temp == A[i][g-1]) && (g>j))
                    {    
                        len ++;
                        g--;
                    }       
                    max_substring = max(max_substring,len);
                }
                break;
            }
        }
        multimap<int,tuple<char,bool,int>> :: iterator mIta;
        if (A[i].size() == count)
        {
            tuple<char,bool,int> p = make_tuple(A[i].front(), true,i);
            
            for(mIta = record.begin(); mIta != record.end(); mIta++)
            {
                if ((get<char>(mIta->second) == get<char>(p)) && get<bool>(mIta->second))
                    break;
            }
            if(mIta != record.end())
            {
                record.insert({count + mIta->first,p});
                record.erase(mIta);
            }
            else
            {
                record.insert({count,p});
            }
            continue;
        }
        tuple<char,bool,int> p = make_tuple(A[i].front(), false,i);
        for(mIta = record.begin(); mIta != record.end(); mIta ++)
            if((mIta->first) == count)
                break;
        if(mIta != record.end())
        {    for(; mIta != record.upper_bound(count); mIta++)
            {
                if (get<char>(mIta->second) == get<char>(p))
                    record.erase(mIta);
                record.insert({count,p});
            }
        }
        else 
                record.insert({count,p});
        count = -1;
        for(int j = (A[i].size()-2); j >= 0; j--)
        {
            if(A[i][j] == A[i].back())
            { 
                count --;
            }
            else break;
        }
        p = make_tuple(A[i].back(), false,i);
        
        for(mIta = record.begin(); mIta != record.end(); mIta ++)
            if((mIta->first) == count)
                break;
        if(mIta != record.end())
        {    for(; mIta != record.upper_bound(count); mIta++)
            {
                if (get<char>(mIta->second) == get<char>(p))
                    record.erase(mIta);
                record.insert({count,p});
            }
        }
        else 
            record.insert({count,p});
    }
    //Tidying up spaghetti code #new implementation in helper for tidyness.
    int retval;
    retval = 0;
    
    auto mItb = record.begin();
    if(record.size() == 1)
        return mItb->first;
    
    auto mIte = record.end();
    --mIte;
    int idx = mItb->first;
    //  Chk postfix
    if(idx < 0)
    {
        while(mItb->first == idx)
        {
            char c = get<char>(mItb->second);
            retval = max(parse_map(record, c, mItb),retval);
            ++mItb;
        }
    }
    // Chk prefix
    mIte = record.end();
    mIte--;
    idx =  mIte->first;
    while(mIte->first == idx)
    {
        char c = get<char>(mIte->second);
        retval = max(parse_map(record, c, mIte),retval);
        --mIte;
    }
    return max(retval,max_substring);
}

int main()
{
    vector<string> A{"aabb", "aaaa", "bbab"};
    vector<string> B{"xxbxx", "xbx", "x"};
    vector<string> C{"dd", "bb", "cc", "dd"};
    vector<string> D{"abbba"};
    vector<string> E{"bb", "b", "aaa", "ab", "bba"};
    vector<string> F{"aaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaa"};
    cout<<"Expected_6 \t"<<"got \t"<<solution(A)<<endl;
    cout<<"Expected_4 \t"<<"got \t"<<solution(B)<<endl;
    cout<<"Expected_4 \t"<<"got \t"<<solution(C)<<endl;
    cout<<"Expected_3 \t"<<"got \t"<<solution(D)<<endl;
    cout<<"Expected_6 \t"<<"got \t"<<solution(E)<<endl;
    cout<<"Expected_24 \t"<<"got \t"<<solution(F)<<endl;
    
}
