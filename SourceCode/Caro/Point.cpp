#include "Point.h"
_Point::_Point()
{
    _x = _y = _check = 0;
}
_Point::_Point(int pX, int pY)
{
    _x = pX; _y = pY;
    _check = 0;
}
bool _Point::setCheck(int pCheck)
{
    if (pCheck == -1 || pCheck == 1 || pCheck == 0)
    {
        _check = pCheck;
        return true;
    }
    return false;
}