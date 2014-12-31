//
//  MinAdjustCost.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/23/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//
/*
 Given an integer array, adjust each integers so that the difference of every adjcent integers are not greater than a given number target.
 If the array before adjustment is A, the array after adjustment is B, you should minimize the sum of |A[i]-B[i]|
 Note, you can assume each number in the array is a positive integer and not greater than 100
E.g.,
 Given [1,4,2,3] and target=1, one of the solutions is [2,3,2,3], the adjustment cost is 2 and it's minimal. Return 2.
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

int** M = 0;

int target = 1;

//Min ajustment cost when we are at index, and after adjustment element at index should be e.
int AdjCost(const vector<int>& v, int index, int e)
{
    if(index==-1)
        return 0;
    if(M[index][e] != -1)
        return M[index][e];
    int m = INT_MAX;
    for(int f=max(1, e-target); f<=min(100, e+target); f++)
    {
        int c = AdjCost(v, index-1, f) + abs(e-v[index]);
        if(c < m)
            m = c;
    }
    cout << index << ' ' << e << ' ' << m << endl;
    M[index][e] = m;
    return m;
}

int mainAdj()
{
    vector<int> v = {1, 4, 2, 3, 5};
    M = new int* [v.size()];
    for(int i=0; i<v.size(); i++)
    {
        M[i] = new int [101];
        memset(M[i], 0xFF, 101*sizeof(int));
    }
    int min = INT_MAX;
    for(int f=1; f<=100; f++)
    {
        int c = AdjCost(v, v.size()-1, f);
        if(c < min)
            min = c;
    }
    cout << min << endl;
    return 0;
}