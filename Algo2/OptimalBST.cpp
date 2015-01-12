//
//  OptimalBST.cpp
//  Algo2
//
//  Created by Wentao Deng on 1/5/15.
//  Copyright (c) 2015 WENTAO INC. All rights reserved.
//
/*Given n keys, each key has probability. How to construct the bi-tree so that we do minimum comparison on average when need to find a key?*/

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

class Solutionx
{
    struct Node
    {
        const pair<char, int>& v; //key and probability pair
        Node* pL = 0;
        Node* pR = 0;
        Node(const pair<char, int>& p) : v(p){};
    };
    
    vector<pair<char, int>>& input;
    vector<vector<int>> CT; //memoization of cost of optimal tree in range [i, j]; root has depth 1.
    vector<vector<int>> CF; //memoization of sum cost in input range [i, j]
    vector<vector<int>> R; //memoization of min cost tree root in range [i, j], element is index in input.
    
public:
    Solutionx(vector<pair<char, int>>& vec) : input(vec)
    {
        sort(input.begin(), input.end());
        CT.resize(input.size(), vector<int>(input.size(), 0));
        CF.resize(input.size(), vector<int>(input.size(), 0));
        R.resize(input.size(), vector<int>(input.size(), 0));
    }
    
    //Create optimal BST from input int the range [start, end] and return min cost
    int optimalBST(int start, int end)
    {
        if(start > end)
            return 0;
        if(CF[start][end]==0)
        {
            for(int i=start; i<=end; i++)
                CF[start][end] += input[i].second;
        }
        if(CT[start][end]!=0)
        {
            return CT[start][end];
        }
        int min = INT_MAX;
        for(int i=start; i<=end; i++)
        {
            int costL = optimalBST(start, i-1);
            int costR = optimalBST(i+1, end);
            int cost = costL + costR + CF[start][end]; // because both children trees has depth 1 lower.
            if(cost < min)
            {
                min = cost;
                R[start][end] = i;
            }
        }
        CT[start][end] = min;
        return min;
    }
    
    //Display tree recursively according to R matrix.
    void display(int start, int end, int indention)
    {
        if(start > end)
            return;
        for(int i=0; i<indention; i++)
            cout << '\t';
        cout << input[R[start][end]].first << endl;
        display(start, R[start][end]-1, indention+1);
        display(R[start][end]+1, end, indention+1);
    }
    
    void solve()
    {
        int cost = optimalBST(0, input.size()-1);
        cout << "Optimal BST cost is " << cost << endl;
        display(0, input.size()-1, 0);
        cout << endl;
        for(auto v : CT)
        {
            for(auto c : v)
                cout << c << '\t';
            cout << endl;
        }
        cout << endl;
        for(auto v : CF)
        {
            for(auto c : v)
                cout << c << '\t';
            cout << endl;
        }
        cout << endl;
        for(auto v : R)
        {
            for(auto c : v)
                cout << input[c].first << '\t';
            cout << endl;
        }
    }
};

int mainOBST()
{
    vector<pair<char, int>> input = {{'c', 23}, {'b', 10}, {'f', 3}, {'d', 14}, {'e', 11}, {'a', 2}, {'g', 16}};
    Solutionx sol(input);
    sol.solve();
    return 0;
}