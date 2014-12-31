//
//  Jump.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/18/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//
/*
 Given an array of non-negative integers, you are initially positioned at the first index of the array.
 
 Each element in the array represents your maximum jump length at that position.
 
 Your goal is to reach the last index in the minimum number of jumps.
 
 For example:
 Given array A = [2,3,1,1,4]
 
 The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
 */

#include <vector>
#include <iostream>
using namespace std;


class Solution {
    int size = 0;
    int* arr = 0;
public:
    
    //return the index of max based on idx.
    //return -1 to indicate a blackhole which is a 0.
    int max(int idx)
    {
        if(arr[idx]==0)
            return -1;
        if(idx+arr[idx]>=size-1)
            return size; // to indicate reaching the end
        int max = 0;
        int index = 0;
        for(int i=idx+1; i<=idx+arr[idx]; i++)
        {
            int bound = arr[i] + i;
            if(bound > max)
            {
                max = bound;
                index = i;
            }
        }
        return index;
    }
    
    int jump(int A[], int n) {
        if(n==1)
            return 0;
        size = n;
        arr = A;
        int steps = 0;
        int next = 0;
        while(next < n-1)
        {
            cout << next << ' ' << endl;
            next = max(next);
            if(next==-1)
                return -1;
            steps++;
        }
        return steps;
    }
};


int mainJump()
{
    Solution sol;
    int a[] = {2,3,1,1,4};
    cout << sol.jump(a, sizeof(a)/sizeof(a[0])) << endl;
    return 0;
}
