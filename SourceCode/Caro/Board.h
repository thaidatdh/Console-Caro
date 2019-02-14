#pragma once
#include "Point.h"
#include "ConsoleWindow.h"
#include "Caro.h"
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
class _Board
{
private:
    int _size;
    int _left, _top;
    _Point** _pArr;
    int _numPlayer1, _numPlayer2;
public:
    vector <_Point> _winningPoints;
public:
    int getSize() { return _size; }
    int getLeft() { return _left; }
    int getTop() { return _top; }
    int getXAt(int i, int j) { return _pArr[i][j].getX(); }
    int getYAt(int i, int j) { return _pArr[i][j].getY(); }
    int getCheckAt(int i, int j) { return _pArr[i][j].getCheck(); }
    int getNumPlayer1() { return _numPlayer1; }
    int getNumPlayer2() { return _numPlayer2; }
private:
    //4 functions below help check the wining player
    bool checkRows(int max, int player);
    bool checkCols(int max, int player);
    bool checkRightCross(int max, int player);
    bool checkLeftCross(int max, int player);
public:
    void resetWinningPoints(); //reset wining points
    void saveBoard(FILE* f); //save current board status
    void loadBoard(FILE* f); //load board status
    void resetData(); //reset data (coordinate and value) of the board
    void drawData(); //draw the board
    int checkBoard(int pX, int pY, bool pTurn); //check icons of player
    int testBoard(bool turn); // check who win the game
    void drawLoadedData(); //draw loaded board from file to console window
public:
    _Board(int pSize, int ptX, int ptY);
    ~_Board();
};
