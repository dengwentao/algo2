//
//  Sudoku.cpp
//  Algo2
//
//  Created by Wentao Deng on 12/27/14.
//  Copyright (c) 2014 WENTAO INC. All rights reserved.
//

/*Write a program to solve a Sudoku puzzle by filling the empty cells.
 Empty cells are indicated by the character '.'.
 You may assume that there will be only one unique solution.*/

#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;
#include "assert.h"


void DisplaySudoku(const vector<vector<char>>& A)
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
                cout << A[i][j] << ' ';
        }
        cout << endl;
    }
}

class Solution {
public:
    
    //try 1-9 in board[i][j]. If successful, return true.
    bool testSudoku(vector<vector<char> > &board, int row, int col,
                    vector<vector<bool>>& rows, vector<vector<bool>>& cols, vector<vector<vector<bool>>>& sqrs)
    {
        int nextCol = (col+1)%9;
        int nextRow = nextCol==0 ? (row+1)%9 : row;
            
        if(board[row][col]!='.')
        {
            if(nextRow==0 && nextCol==0)
                return true;
            return testSudoku(board, nextRow, nextCol, rows, cols, sqrs);
        }
        
        for(int k='1'; k<='9'; k++)
        {
            if(rows[row][k-'0'] || cols[col][k-'0'] || sqrs[row/3][col/3][k-'0'])
                continue;
            rows[row][k-'0'].flip();
            cols[col][k-'0'].flip();
            sqrs[row/3][col/3][k-'0'].flip();
            board[row][col] = k;
            if(nextRow==0 && nextCol==0)
                return true;
            if(testSudoku(board, nextRow, nextCol, rows, cols, sqrs))
                return true;
            else
            {
                rows[row][k-'0'].flip();
                cols[col][k-'0'].flip();
                sqrs[row/3][col/3][k-'0'].flip();
                board[row][col] = '.';
            }
        }
        return false;
    }
    
    void solveSudoku(vector<vector<char> > &board) {
        vector<bool> b(10, false);
        vector<vector<bool>> rows(9, b);
        vector<vector<bool>> cols(9, b);
        vector<vector<vector<bool>>> sqrs(3, {b, b, b});
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
            {
                if(board[i][j]=='.')
                    continue;
                rows[i][board[i][j]-'0'].flip();
                cols[j][board[i][j]-'0'].flip();
                sqrs[i/3][j/3][board[i][j]-'0'].flip();
            }
        testSudoku(board, 0, 0, rows, cols, sqrs);
    }
};

int mainSudoku()
{
    vector<vector<char>> board =
                  {   {'5','3','.','.','7','.','.','.','.'},
                      {'6','.','.','1','9','5','.','.','.'},
                      {'.','9','8','.','.','.','.','6','.'},
                      {'8','.','.','.','6','.','.','.','3'},
                      {'4','.','.','8','.','3','.','.','1'},
                      {'7','.','.','.','2','.','.','.','6'},
                      {'.','6','.','.','.','.','2','8','.'},
                      {'.','.','.','4','1','9','.','.','5'},
                      {'.','.','.','.','8','.','.','7','9'}};
    DisplaySudoku(board);
    
    Solution sol;
    sol.solveSudoku(board);
    DisplaySudoku(board);
    
    return 0;
}