//
//  main.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/15/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

#include <iostream>
#include <climits>
#include <vector>
#include <stack>
using namespace std;

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


int mainX()
{
    MinStack s;
    s.push(-2);
    s.push(0);
    s.push(-1);
   // s.push(3);
//    s.pop();
//    s.pop();
    cout << s.getMin() << ' ' << s.top() << endl;
    s.pop();
    cout << s.getMin() << ' ' << s.top() << endl;
    s.push(6);
    //s.push(3);
    cout << s.getMin() << ' ' << s.top() << endl;
    return 0;
}


