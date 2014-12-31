//
//  FirstMissingPositive.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/27/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

/*
 Given an unsorted integer array, find the first missing positive integer.
 
 For example,
 Given [1,2,0] return 3,
 and [3,4,-1,1] return 2.
 
 Your algorithm should run in O(n) time and uses constant space.
 */

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        //even though we visit a slot that has already been adjusted, we simply do nothing.
        for(int i=0; i<n; i++)
        {
            int cur = A[i];
            //if we finished one loop, it will be A[cur-1]==cur so we don't repeat.
            while(cur>0 && cur<=n && A[cur-1]!=cur) //no need to adjust for these values
            {
                int tmp = A[cur-1];
                A[cur-1] = cur;
                cur = tmp;
            }
        }
        for(int i=0; i<n; i++)
        {
            if(A[i]!=i+1)
                return i+1;
        }
        return n+1;
    }
};

int mainMiss()
{
    int A[] = {-1,1,0,-2,-4,2,3};
    Solution sol;
    cout << sol.firstMissingPositive(A, sizeof(A)/sizeof(A[0])) << endl;
    return 0;
}