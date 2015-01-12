//
//  TopoSort.cpp
//  Algo2
//
//  Created by Wentao Deng on 1/6/15.
//  Copyright (c) 2015 WENTAO INC. All rights reserved.
//

/*Given a list of pairs (a->b), print one sorted version.*/

#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"

//When there's cyclic, we simply don't output that part.
void Toposort2(const vector<pair<char, char>>& input)
{
    queue<char> q;
    unordered_map<char, unordered_set<char>> outgoing; //for each node, its outgoing nodes
    unordered_map<char, unordered_set<char>> incoming; //for each node, its incoming nodes
    
    for(auto p : input)
    {
        outgoing[p.first].insert(p.second);
        incoming[p.second].insert(p.first);
    }
    
    //find all outgoing nodes that have no incoming
    for(auto o : outgoing)
    {
        if(incoming.find(o.first) == incoming.end())
            q.push(o.first);
    }

    while(!q.empty())
    {
        char c = q.front();
        cout << c << ' ';
        q.pop();
        for(char i : outgoing[c])
        {
            incoming[i].erase(c);
            if(incoming[i].empty())
                q.push(i);
        }
    };
}

class DAG
{
    unordered_map<char, vector<char>> adj; //adjacent list to represent this DAG.
    unordered_set<char> visited; //indicate if a node is visited
    stack<char> s; //to hold the path
    
    //recursively visit vertex v for each of its adjacent vertices
    void TopoVisit(char v)
    {
        if(visited.find(v) != visited.end())
            return;
        visited.insert(v);
        
        for(char c: adj[v])
        {
            TopoVisit(c);
        }
        
        s.push(v);
    }
    
public:
    DAG(const vector<pair<char, char>>& input)
    {
        for(auto p : input)
            adj[p.first].push_back(p.second);
    }
    
    void TopoSort()
    {
        for(auto v : adj)
            TopoVisit(v.first);
        while(!s.empty())
        {
            cout << s.top() << ' ';
            s.pop();
        }
    }
};



//Another way based on DFS.
void Toposort1(const vector<pair<char, char>>& input)
{
    DAG dag(input);
    dag.TopoSort();
}

int main()
{
    vector<pair<char, char>> input = {{'a', 'g'}, {'a', 'h'}, {'g', 'e'}, {'x', 'y'}, {'y', 'x'}, {'e', 'h'}, {'g', 'h'}, {'h', 'i'}, {'h', 'k'}};
    Toposort1(input);
    cout << endl;
    Toposort2(input);
    return 0;
}



