#pragma once
class _Point 
{
private:
    int _x, _y, _check;
public:
    int getX() { return _x; }
    int getY() { return _y; }
    int getCheck() { return _check; }
    void setX(int ptX) { _x = ptX; }
    void setY(int ptY) { _y = ptY; }
    bool setCheck(int pCheck);
public:
    _Point();
    _Point(int pX, int pY);
};