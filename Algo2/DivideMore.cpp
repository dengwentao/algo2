//
//  DivideMore.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/18/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//
/*
 Divide number and return result in form of a string. e.g 100/3 result should
 be 33.(3) Here 3 is in brackets because it gets repeated continuously and 5
 /10 should be 0.5.
 */

#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
using namespace std;
#include "assert.h"


string get_decimal(int num, int den)
{
    int quote = num / den;
    int remainder = num % den;
    int pos = 0;
    string ret;
    unordered_map<int, int> maps; //mapping between remainder and position
    while(maps.find(remainder)==maps.end())
    {
        maps[remainder] = pos;
        ret.append(to_string(remainder*10 / den));
        remainder = (remainder*10 % den);
        pos++;
    }
    
    ret.insert(maps[remainder], "(");
    ret.push_back(')');
    ret.insert(0, to_string(quote)+'.');

    return ret;
}

int mainDivision()
{
    assert(get_decimal(1, 6) == "0.1(6)");
    assert(get_decimal(2, 3) == "0.(6)");
    assert(get_decimal(1, 11) == "0.(09)");
    assert(get_decimal(1, 17) == "0.(0588235294117647)");
    assert(get_decimal(7, 12) == "0.58(3)");
    assert(get_decimal(10, 5) == "2.(0)");
    assert(get_decimal(0, 5) == "0.(0)");
    return 0;
}