//
//  WildcardMatching.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/31/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//
/*
 '?' Matches any single character.
 '*' Matches any sequence of characters (including the empty sequence).
*/

#include <vector>
#include <stack>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

class Solution {
    vector<vector<int>> M;
public:
    
    bool isMatch(const char *s, const char *p, int i, int j)
    {
        if(s[i]==0 && p[j]==0)
            return true;
        else if(p[j]==0)
            return false;
        if(M[i][j]!=-1)
            return M[i][j];
        
        M[i][j] = false;
        if(p[j+1]!='*') 
        {
            if(s[i]==0)
                M[i][j] = false;
            else if(s[i]==p[j] || p[j]=='.')
                M[i][j] = isMatch(s, p, i+1, j+1);
        }
        else
        {
            if(p[j] != '.')
            {
                M[i][j] = (s[i]==p[j] && isMatch(s, p, i+1, j)) || isMatch(s, p, i, j+2);
            }
            else
            {
                //.* could match 0 or all, so k should starts from i and end with '\0'
                for(int k=i; k<=strlen(s); k++)
                {
                    bool b = isMatch(s, p, k, j+2);
                    if(b)
                    {
                        M[i][j] = b;
                        break;
                    }
                }
            }
        }
            
        return M[i][j];
    }
    
    bool isMatch(const char *s, const char *p) {
        if(p[0]==0)
            return s[0]==0;
        M.resize(strlen(s)+1, vector<int>(strlen(p)+1, -1));
        return isMatch(s, p, 0, 0);
    }
    
    void display()
    {
        for(vector<int> v : M)
        {
            for(int i : v)
                cout << i << '\t';
            cout << endl;
        }
    }
};

int mainRegex()
{
    Solution sol;
    cout << sol.isMatch("a", ".*..a*") << endl;
    sol.display();
    return 0;
}