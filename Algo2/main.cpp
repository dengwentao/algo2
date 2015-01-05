//
//  main.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/15/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <utility>
#include <unordered_map>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

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



int mainX()
{
    vector<list<pair<int, string>>> indexes = {{{1, "a"}, {3, "c"}, {4, "b"}}, {{2, "a"}, {5, "b"}}};
    for(auto l : indexes)
    {
        for(auto p : l)
            cout << p.first << ' ' << p.second << endl;
    }

    
    vector<pair<int, string>> pairs = multiMergeSort(indexes);
    for(pair<int, string> p : pairs)
        cout << p.first << ' ' << p.second << endl;
    return 0;
}


