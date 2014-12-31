//
//  LongestValidParentheses.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/31/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//
/*Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 
 For "(()", the longest valid parentheses substring is "()", which has length = 2.
 
 Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.*/

#include <vector>
#include <stack>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<pair<char, int>> st;
        int max = 0;
        st.push(make_pair('#', -1));
        for(int i=0; i<s.length(); i++)
        {
            if(s[i]=='(')
                st.push(make_pair('(', i));
            else
            {
                if(st.empty())
                {
                    st.push(make_pair(')', i));
                    continue;
                }
                pair<char, int> top = st.top();
                if(top.first == '(')
                {
                    st.pop();
                    top = st.top();
                    int len = i - top.second;
                    if(len > max)
                        max = len;
                }
                else
                    st.push(make_pair(')', i));
            }
        }
        return max;
    }
};

int main()
{
    Solution sol;
    cout << sol.longestValidParentheses("()") << endl;
    return 0;
}