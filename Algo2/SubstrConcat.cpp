//
//  SubstrConcat.cpp
//  Algo2
//
//  Created by Wentao Deng on 1/2/15.
//  Copyright (c) 2015 WENTAO INC. All rights reserved.
//

/*You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters.
 For example, given:
 S: "barfoothefoobarman"
 L: ["foo", "bar"]
 Note that L could be dups such as [foo, bar, foo]; overlapping is also allowed. foobarfoo and [foo, bar] returns 0, 3
 You should return the indices: [0,9]. (order does not matter).*/

#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

class Solution2 {
    
    // compare two lists
    struct LessList
    {
        bool operator()(const list<pair<int, string>>* l1, const list<pair<int, string>>* l2) const
        {
            // we use > for less because priority queue is a max heap.
            return l1->front().first > l2->front().first;
        }
    };
    
    // multiway merge sort on sorted lists.
    // use list because we need to remove front.
    vector<pair<int, string>> multiMergeSort(vector<list<pair<int, string>>>& indexes)
    {
        vector<pair<int, string>> res;
        priority_queue<list<pair<int, string>>*, vector<list<pair<int, string>>*>, LessList> pq;
        
        //push each list into the priority queue.
        for(int i=0; i<indexes.size(); i++)
        {
            if(!indexes[i].empty())
                pq.push(&indexes[i]);
        }
        
        while(!pq.empty())
        {
            list<pair<int, string>>* l = pq.top();  //the list which has min front value
            pq.pop();
            res.push_back(l->front());
            l->pop_front();
            if(!l->empty())
                pq.push(l);
        }
        
        return res;
    }
    
    //Get sorted <index, substring> pairs
    vector<pair<int, string>> getIndexes(const string& S, const vector<string> &L)
    {
        int len = L[0].length();
        
        //scan each substrings for their positions
        vector<list<pair<int, string>>> indexes;
        for(string sub : L)
        {
            list<pair<int, string>> pairs; // for a single substring, get all its indexes
            int pos = 0;
            while(true)
            {
                pos = S.find(sub, pos);
                if(pos == S.npos)
                    break;
                else
                {
                    pairs.push_back(make_pair(pos, sub));
                    pos += len;
                }
            }
            indexes.push_back(pairs);
        }
        
        return multiMergeSort(indexes);
    }
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        vector<int> res;
        int size = L.size();
        if(size==0 || S.empty())
            return res;
        int len = L[0].length();
        if(len==0)
            return res;
        
        vector<pair<int, string>> indexes = getIndexes(S, L);
        
        //check combinations in a sliding window of k where k is size of L.
        //in this window, when it's a arithmatic progression of len and there're k different strings, it's valid.
        unordered_map<string, int> map; // substring and its count in current window
        queue<int> window; // sliding window, int is index in indexes array
        for(int i=0; i<indexes.size(); i++)
        {
            cout << indexes[i].first << ' ' << indexes[i].second << endl;
            if(map.size() < size)
            {
                map[indexes[i].second] += 1;
                window.push(i);
                if(window.size() > size)
                    window.pop();
            }
            if(map.size() == size) //we inserted in the block upper.
            {
                //now that we have all substrings in this window, check if it's valid
                bool valid = true;
                int dock = indexes[window.front()].first;
                int prev = dock-len;
                while(!window.empty())
                {
                    int index = indexes[window.front()].first;
                    if(index-prev != len)
                    {
                        valid = false;
                        break;
                    }
                    string sub = indexes[window.front()].second;
                    map[sub] -= 1;
                    if(map[sub] == 0)
                        map.erase(sub);
                    window.pop(); //consume this element.
                    prev = index;
                }
                if(valid)
                    res.push_back(dock);
            }
        }
        
        return res;
    }
};


class Solution3 {
    bool equal(unordered_map<string, int>& pattern,  unordered_map<string, int>& window)
    {
        for(auto p : pattern)
        {
            if(p.second != window[p.first])
                return false;
        }
        return true;
    }
    
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        vector<int> res;
        int size = L.size();
        if(size==0 || S.empty())
            return res;
        int len = L[0].length();
        if(len==0)
            return res;
        
        //first scan each substrings for their positions
        vector<pair<int, string>> indexes; //index - substring pairs, ordered by index.
        for(int i=0; i<S.length(); i++)
        {
            for(string sub : L)
            {
                if(0 == S.compare(i, len, sub))
                {
                    //cout << i << ' ' << sub << endl;
                    indexes.push_back(make_pair(i, sub));
                    i += len-1; // -1 because of i++
                    break;
                }
            }
        }

        unordered_map<string, int> patterns;
        for(string s : L)
            patterns[s] += 1;
        
        //check combinations in a sliding window of k where k is size of L.
        //in this window, when it's a arithmatic progression of len and there're k different strings, it's valid.
        unordered_map<string, int> map; // substring and its count in current window
        queue<int> window; // sliding window, int is index in indexes array
        for(int i=0; i<indexes.size(); )
        {
            
            while(!equal(patterns, map) && i<indexes.size())
            {
                cout << indexes[i].first << ' ' << indexes[i].second << endl;
                map[indexes[i].second] += 1;
                window.push(i);
                if(window.size() > size)
                    window.pop();
                i++;
            }
            
            if(i==indexes.size() && !equal(patterns, map)) // a special case
                break;
            
            //just do it.
            {
                //now that we have all substrings in this window, check if it's valid
                bool valid = true;
                int dock = indexes[window.front()].first;
                int prev = dock-len;
                while(!window.empty())
                {
                    int index = indexes[window.front()].first;
                    if(index-prev != len)
                    {
                        valid = false;
                        break;
                    }
                    string sub = indexes[window.front()].second;
                    map[sub] -= 1;
                    window.pop(); //consume this element.
                    prev = index;
                }
                if(valid)
                    res.push_back(dock);
            }
        }
        
        return res;
    }
};


class Solution {
    // check if two hash maps are equal
    bool equal(const unordered_map<string, int>& pattern,  unordered_map<string, int>& window)
    {
        for(auto p : pattern)
        {
            if(p.second != window[p.first])
                return false;
        }
        return true;
    }
    
    //scan each substrings for their positions
    vector<pair<int, string>> getIndexes(const string& S, const vector<string>& L)
    {
        int len = L[0].length();
        vector<pair<int, string>> indexes; //index - substring pairs, ordered by index.
        for(int i=0; i<S.length(); i++)
        {
            for(string sub : L)
            {
                if(0 == S.compare(i, len, sub))
                {
                    //cout << i << ' ' << sub << endl;
                    indexes.push_back(make_pair(i, sub));
                    break;
                }
            }
        }
        return indexes;
    }
    
    //scan for valid patterns in indexes
    //len is substring length and size is count of L items.
    vector<int> scanPatterns(const vector<pair<int, string>>& indexes, const unordered_map<string, int>& patterns, int len, int size)
    {
        vector<int> res;
        if(indexes.empty())
            return res;
        vector<pair<int, string>> remainders; //to hold remainders in indexes.
        //check combinations in a sliding window of k where k is size of L.
        //in this window, when it's a arithmatic progression of len and there're k different strings, it's valid.
        unordered_map<string, int> map; // substring and its count in current window
        list<int> window; // sliding window, int is index in indexes array
        int prev = -len;
        for(int i=0; i<indexes.size(); i++)
        {
            cout << indexes[i].first << ' ' << indexes[i].second << endl;
            if(indexes[i].first - prev < len)
            {
                remainders.push_back(indexes[i]);
                continue;
            }
            else if(indexes[i].first - prev > len)
            {
                //window is not full while an invalid entry is coming, we should clear current window
                window.clear();
                map.clear();
            }
            prev = indexes[i].first;
            window.push_back(i);
            map[indexes[i].second] += 1;
            
            if(window.size() == size)
            {
                //now that window is full, check if it's valid
                auto front = indexes[window.front()]; //window's front element
                if(equal(patterns, map))
                    res.push_back(front.first);
                //pop front as window has to slide right one
                map[front.second] -= 1;
                window.pop_front();
            }
        }
        vector<int> more = scanPatterns(remainders, patterns, len, size);
        res.insert(res.end(), more.begin(), more.end());
        return res;
    }
    
public:
    vector<int> findSubstring(string S, vector<string> &L) {
        
        if(L.size()==0 || L[0].length()==0 || S.empty())
            return vector<int>();
        
        //statistics for substrings patterns
        unordered_map<string, int> patterns;
        for(string s : L)
            patterns[s] += 1;
        
        //first scan each substrings for their positions
        vector<pair<int, string>> indexes = getIndexes(S, L);
        
        return scanPatterns(indexes, patterns, L[0].length(), L.size());
    }
};

int main()
{
    string s = "abaababbaba";
    vector<string> L = {"ab","ba","ab","ba"};
    Solution sol;
    vector<int> indexes = sol.findSubstring(s, L);
    for(int index : indexes)
        cout << index << ' ';
    return 0;
}
