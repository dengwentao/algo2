//
//  Intervals.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/16/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

#include <vector>
#include <iostream>
using namespace std;

struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
 };
 

class Solution2 {
    /*
     Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
     
     You may assume that the intervals were initially sorted according to their start times.
     
     Example 1:
     Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
     
     Example 2:
     Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].
     
     This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
     */

    vector<Interval> heads; //intervals in front of the new interval
    vector<Interval> overlaps; //intervals overlapping with the new interval.
    vector<Interval> tails; //intervals behind the new interval
public:
    
    //partition the input into 3 parts, headers, overlaps, and tails.
    void partition(const vector<Interval> &intervals, const Interval& newInterval)
    {
        for(int i=0; i<intervals.size(); i++)
        {
            if(newInterval.start > intervals[i].end)
                heads.push_back(intervals[i]);
            else if(newInterval.end < intervals[i].start)
                tails.push_back(intervals[i]);
            else
                overlaps.push_back(intervals[i]);
        }
     }
    
    //combine 2 overlapped intervals into 1
    Interval combine(const Interval& i1, const Interval& i2)
    {
        int start = i1.start < i2.start ? i1.start : i2.start;
        int end = i1.end > i2.end ? i1.end : i2.end;
        return Interval(start, end);
    }
    
    //insert the new into the overlapped intervals
    Interval insert_overlaps(vector<Interval> &intervals, Interval newInterval)
    {
        Interval result = newInterval;
        for(Interval iv : intervals)
        {
            result = combine(result, iv);
        }
        return result;
    }
    
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        partition(intervals, newInterval);
        Interval ovl = insert_overlaps(overlaps, newInterval);
        vector<Interval> res;
        res.insert(res.end(), heads.begin(), heads.end());
        res.push_back(ovl);
        res.insert(res.end(), tails.begin(), tails.end());
        return res;
    }
};

int main2()
{
    vector<Interval> intervals = {Interval(1,2), Interval(3,5), Interval(6,7), Interval(8,10), Interval(12,16)};
    Interval intv(4,9);
    Solution2 sol;
    vector<Interval> new_intvs = sol.insert(intervals, intv);
    for(Interval itv : new_intvs)
        cout << itv.start << '\t' << itv.end << endl;
    return 0;
}

class Solution {
/*
 Given a collection of intervals, merge all overlapping intervals.
 
 For example,
 Given [1,3],[2,6],[8,10],[15,18],
 return [1,6],[8,10],[15,18].
 */
    static bool compare (const Interval& iv1, const Interval& iv2) { return iv1.start < iv2.start; }
    
    //combine 2 intervals i1 and i2 into 1. i1 to put the result. If no combination, return false.
    bool combine(Interval& i1, const Interval& i2)
    {
        if(i1.end < i2.start || i1.start > i2.end)
            return false;
        i1.start = i1.start < i2.start ? i1.start : i2.start;
        i1.end = i1.end > i2.end ? i1.end : i2.end;
        return true;
    }

public:
    vector<Interval> merge(vector<Interval> &intervals) {
        if(intervals.size()<2)
            return intervals;
        sort(intervals.begin(), intervals.end(), Solution::compare);
        vector<Interval> result;
        Interval iv = intervals[0];
        for(int i=1; i<intervals.size(); i++)
        {
            if(!combine(iv, intervals[i]))
            {
                result.push_back(iv);
                iv = intervals[i];
            }
        }
        result.push_back(iv);
        return result;
    }
};

int mainInv2()
{
    vector<Interval> intervals = {Interval(1,3), Interval(2,6), Interval(6,10), Interval(15,18)};
    Solution sol;
    vector<Interval> new_intvs = sol.merge(intervals);
    for(Interval itv : new_intvs)
        cout << itv.start << '\t' << itv.end << endl;
    return 0;
}