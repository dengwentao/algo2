//
//  MaxGap.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/29/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

/*
 Given an array A of n distinct numbers. Design an linear time algorithm to find two elements x, y in A maximizing x – y, subject to x < y and no element z in A satisfies x < z < y.
 */

#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

class Solution {
    struct Slot
    {
        vector<int> range; //hold the min and max of this slot only.
        
        //to insert a new value into this slot.
        //make sure range[0] < range[1]. For dups, ignore.
        void insert(int v)
        {
            int sz = range.size();
            if(sz==0)
                range.push_back(v);
            else if(sz==1)
            {
                int first = range[0];
                if(v > first)
                    range.push_back(v);
                else if(v < first)
                {
                    range.push_back(first);
                    range[0] = v;
                }
                else
                    return;
            }
            else
            {
                if(v < range[0])
                    range[0] = v;
                else if(v > range[1])
                    range[1] = v;
                else
                    return;
            }
        };
    };
    
    vector<Slot> slots;
    float gap;
    int min;
    int max;
    int size;
    
    //return the index of gaps where v should go
    int index(int v)
    {
        return floor((v - min) / gap);
    };
    
public:
    int maximumGap(vector<int> &num) {
        if(num.size() < 2)
            return 0;
        min = *min_element(num.begin(), num.end());
        max = *max_element(num.begin(), num.end());
        size = num.size() - 1;
        gap = (max - min) / (float)size;
        slots.resize(size);
        
        for(int v : num)
        {
            if(v!=min && v!=max)
                slots[index(v)].insert(v);
        }
        
        int maxGap = 0;
        int prev = min;
        for(int i=0; i<slots.size(); i++)
        {
            for(int x : slots[i].range)
            {
                int gap = x - prev;
                if(gap > maxGap)
                    maxGap = gap;
                prev = x;
            }
        }
        if(max-prev > maxGap)
            maxGap = max - prev;
        return maxGap;
    };
};

class Solution2 {
    vector<bool> set;
public:
    int maximumGap(vector<int> &num) {
        if(num.size() < 2)
            return 0;
        int min = *min_element(num.begin(), num.end());
        int max = *max_element(num.begin(), num.end());
        for(int v : num)
            v = v - min;
        set.resize(max-min+1);
        for(int v : num)
            set[v] = true;
        int gap = 0;
        int prev = 0;
        for(int i=0; i<set.size(); i++)
        {
            if(set[i])
            {
                if(gap < i-prev)
                    gap = i-prev;
                prev = i;
            }
        }
        return gap;
    }
};

int mainGapMax()
{
    vector<int> v = {1,3,12,0,7,7};
    Solution sol;
    cout << sol.maximumGap(v) << endl;
    return 0;
}