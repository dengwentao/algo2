//
//  main.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/15/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <climits>
#include <vector>
#include <stack>
using namespace std;
#include <assert.h>

class MinStack
{
    stack<int> s;
    stack<int> min;
public:
    MinStack() = default;
    ~MinStack() = default;

    int top()
    {
        if(s.size()==0)
            throw "empty stack";
        return s.top();
    }

    int getMin()
    {
        if(min.size()==0)
            throw "empty stack";
        return min.top();
    }

    void push(int v)
    {
        int m = min.size()==0 ? INT_MAX : min.top();
        s.push(v);
        if(v <= m) //consider dups
            min.push(v);
    }

    void pop()
    {
        if(s.size()==0)
            throw "empty stack";
        int v = s.top();
        s.pop();
        int m = min.top();
        if(v == m) //consider dups
            min.pop();
    }
};

bool isAnagram(const string string1, const string& string2)
{
    unordered_map<char, int> map;
    for(char c : string1)
        map[c] += 1;
    for(char c : string2)
    {
        map[c] -= 1;
        if(map[c]==0)
            map.erase(c);
    }
    return map.size()==0;
}



int mainX()
{
    assert(isAnagram("", ""));
    assert(!isAnagram("", "ab"));
    assert(!isAnagram("aa", ""));
    assert(isAnagram("aa", "aa"));
    assert(isAnagram("abc", "cba"));
    return 0;
}


