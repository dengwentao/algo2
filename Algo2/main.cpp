//
//  main.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/15/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

bool incr(vector<int>& v)
{
    int min = INT_MAX;
    int mid = INT_MAX;
    for(int i : v)
    {
        if(i <= min)
            min = i;
        else if(i <= mid)
            mid = i;
        else
            return true;
    }
    return false;
}

int mainX()
{
    vector<int> v = {3, 2, -2, 3, 4};
    cout << incr(v) << endl;
    return 0;
}

