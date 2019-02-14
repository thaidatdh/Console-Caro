#pragma once
#include "Point.h"
class _Player
{
private:
    int _numChecked;
    int _winCount;
public:
    int getWinCount() { return _winCount; }
    int getNumChecked() { return _numChecked; }
public:
    void increaseNumChecked();
    void increaseWinCount();
    void resetNumChecked();
    void resetWinCount();
public:
    _Player();
};