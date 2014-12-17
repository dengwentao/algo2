//
//  ValidNumber.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/15/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//
/*
 Validate if a given string is numeric.
 Some examples:
 "0" => true      Format A
 " 0.1 " => true  Format B
 "abc" => false
 "1 a" => false
 "2e10" => true   Format C which is in format BeA
 */


#include <iostream>
using namespace std;


class Solution {
    
public:
    //in format 120 or 003, no sign
    bool isBasicFormat(const string& s)
    {
        //if(s.empty())
        //    return false;
        for(char c : s)
            if(c<'0' || c>'9')
                return false;
        return true;
    }
    
    //in format +120
    bool isFormatA(const string& s)
    {
        //if(s.empty())
        //    return false;
        if(s[0]=='+' || s[0]=='-')
            return isBasicFormat(s.substr(1));
        else
            return isBasicFormat(s);
    }
    
    //in format -3.120
    bool isFormatB(const string& s)
    {
        int pos = s.find('.');
        if(pos==string::npos)
            return false;
        if(s.length()==1)
            return false;
        string front = s.substr(0, pos);
        string end = s.substr(pos+1);
        if( front.length()==1 && (front[0]=='+' || front[0]=='-') && end.empty())
            return false;
        return isFormatA(front) && isBasicFormat(end);
    }
    
    //in format -3.2e-2
    bool isFormatC(const string& s)
    {
        int pos = s.find('e');
        if(pos==string::npos)
            return false;
        string front = s.substr(0, pos);
        string end = s.substr(pos+1);
        if(front.empty() || end.empty())
            return false;
        if(  front.length()==1 && (front[0]=='+' || front[0]=='-')
           ||end.length()==1 && (end[0]=='+' || end[0]=='-'))
            return false;
        return (isFormatB(front) || isFormatA(front)) && isFormatA(end);
    }
    
    bool isNumber(const char *s) {
        string input = s;
        input.erase(0, input.find_first_not_of(" \n\r\t"));
        input.erase(input.find_last_not_of(" \n\r\t")+1);
        if(input.empty())
            return false;
        return isFormatA(input) || isFormatB(input) || isFormatC(input);
    }
};

int mainNum()
{
    Solution sol;
    cout << sol.isNumber("-.1") << endl;
    return 0;
}
