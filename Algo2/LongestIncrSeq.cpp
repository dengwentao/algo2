//
//  LongestIncrSeq.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/19/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

#include <vector>
#include <iostream>
using namespace std;
#include "assert.h"

//Find the position of first value greater than a.
//If not found, i.e., larger than all, return -1.
//no dup.
int Position(const vector<int>& b, int a)
{
    if(b.empty() || a > b.back())
        return -1;
    int low = 0;
    int high = b.size() - 1;
    while(low+1 <= high)
    {
        int med = (high-low)/2 + low;
        if(b[med] < a)
            low = med + 1;
        else if(b[med] > a)
            high = med;
        else
        {
            high = med;
            break;
        }
    }
    return high;
}

int LIS(const vector<int>& v)
{
    vector<int> b;
    for(int a : v)
    {
        int pos = Position(b, a);
        if(pos==-1)
            b.push_back(a);
        else
            b[pos] = min(a, b[pos]);
    }
    return b.size();
}

int mainIncrSeq()
{
    vector<int> v = {2, 1, 5, 3, 6, 4, 8, 9, 7};
    cout << LIS(v) << endl;
    //vector<int> v2 = {-2, 1, 3, 5, 6, 8, 9, 17};
    //cout << Position(v2, -1) << endl;
    return 0;
}