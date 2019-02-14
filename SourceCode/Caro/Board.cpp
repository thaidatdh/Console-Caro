#include "Board.h"
_Board::_Board(int pSize, int ptX, int ptY)
{
    _numPlayer1 = _numPlayer2 = 0;
    _size = pSize;
    _left = ptX;
    _top = ptY;
    _pArr = new _Point*[pSize];
    for (int i = 0; i < pSize; i++)
        _pArr[i] = new _Point[pSize];
}
_Board::~_Board()
{
    for (int i = 0; i < _size; i++)
        delete[] _pArr[i];
    delete[] _pArr;
}
void _Board::saveBoard(FILE *f)
{
    if (_size == 0) return;
    fwrite(&_size, sizeof(int), 1, f);
    fwrite(&_left, sizeof(int), 1, f);
    fwrite(&_top, sizeof(int), 1, f);
    for (int i = 0; i < _size; i++)
    {
        fwrite(_pArr[i], sizeof(_Point), _size, f); 
    }
}
void _Board::loadBoard(FILE* f)
{
    fread_s(&_size, sizeof(int), sizeof(int), 1, f);
    fread_s(&_left, sizeof(int), sizeof(int), 1, f);
    fread_s(&_top, sizeof(int), sizeof(int), 1, f);
    for (int i = 0; i < _size; i++)
    {
        fread_s(_pArr[i], sizeof(_Point)*_size, sizeof(_Point), _size, f);
    }
}
void _Board::resetData()
{
    if (_size == 0) return; //call constructer before resetData
    _numPlayer1 = _numPlayer2 = 0;
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            _pArr[i][j].setX(4 * j + _left + 2); //x coordinate
            _pArr[i][j].setY(2 * i + _top + 1); //y coordinate
            _pArr[i][j].setCheck(0);
        }
    }
}

void _Board::drawData()//Draw the board //same structure like _Common::DrawRect()
{
    if (_pArr == NULL) return; //call constructor first
    int left = _left;
    int top = _top;
    //Print top line
    _Common::gotoXY(left, top);
    top++;
    cout << char(218); //start top line
    for (int i = 0; i < _size - 1; i++)
    {
        cout << char(196) << char(196) << char(196) << char(194); //middle of top line 
    }
    cout << char(196) << char(196) << char(196) << char(191); //end top line

                                                              //Print middle lines
    _Common::gotoXY(left, top);
    top++;
    for (int i = 0; i < _size - 1; i++) //print two line (1 with spaces, 1 witn crosses) = a block
    {
        //Print lines with spaces
        for (int i = 0; i <= _size; i++)
        {
            cout << char(179); //start line (line with spaces)
            cout << "   ";     //spaces between block
        }
        _Common::gotoXY(left, top);
        top++;
        //Print lines with crosses
        cout << char(195); //start line with crosses
        for (int i = 0; i < _size - 1; i++)
        {
            cout << char(196) << char(196) << char(196) << char(197); //middle line with cross
        }
        cout << char(196) << char(196) << char(196) << char(180); //end line
        _Common::gotoXY(left, top);
        top++;
    }
    //Print last line of blocks
    //Print last line with spaces (line number _size-1)
    for (int i = 0; i <= _size; i++)
    {
        cout << char(179) << "   ";
    }

    //Print last line (bottom)
    _Common::gotoXY(left, top);
    top++;
    cout << char(192); //start line
    for (int i = 0; i < _size - 1; i++)
    {
        cout << char(196) << char(196) << char(196) << char(193); //middle line
    }
    cout << char(196) << char(196) << char(196) << char(217); //end line

    _Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY()); //move current pointer to first block of the board
}
void _Board::drawLoadedData()
{
    if (_pArr == NULL) return; //call constructer first
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            _Common::gotoXY(_pArr[i][j].getX(), _pArr[i][j].getY());
            if (_pArr[i][j].getCheck() == -1)
            {
                _Common::setTextColor(4);
                printf("X");
            }
            else if (_pArr[i][j].getCheck() == 1)
            {
                _Common::setTextColor(11);
                printf("O");
            }
        }
    }
    _Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY()); //move current pointer to first block of the board
}
int _Board::checkBoard(int pX, int pY, bool pTurn)
{
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0)
            {
                if (pTurn) //if current turn is true (pTurn==true): c = -1
                {
                    _pArr[i][j].setCheck(-1);
                    _numPlayer1++;
                }
                else //if current turn is false (pTurn==false): c=1
                {
                    _pArr[i][j].setCheck(1);
                    _numPlayer2++;
                }
                return _pArr[i][j].getCheck();
            }
        }
    }
    return 0;
}
void _Board::resetWinningPoints()
{
    while (_winningPoints.size() != 0)
        _winningPoints.pop_back();
}
bool _Board::checkRows(int max, int player)
{
    bool first = false, last = false;
    for (int row = 0; row < _size; row++)
    {
        for (int col = 0; col < _size - max + 1; col++)
        {
            first = false, last = false;
            int count = 1;
            if (getCheckAt(row, col) == player)
            {
                if (col != 0 && getCheckAt(row, col - 1) == -player)
                    first = true;
                _winningPoints.push_back(_pArr[row][col]);
                for (int k = col + 1; k - col + 1 <= max; k++)
                {
                    if (getCheckAt(row, k) == getCheckAt(row, col))
                    {
                        count++;
                        _winningPoints.push_back(_pArr[row][k]);
                    }
                    else
                    {
                        col = k;
                        break;
                    }
                }
                if (col + max < _size && count == max && getCheckAt(row, col + max) == -player)
                    last = true;

                if (count == max && (first == false || last == false))
                    return true;
                else
                    resetWinningPoints();
            }
        }
    }
    return false;
}
bool _Board::checkCols(int max, int player)
{
    bool first = false, last = false;
    for (int col = 0; col < _size; col++)
    {
        for (int row = 0; row < _size - max + 1; row++)
        {
            first = false, last = false;
            int count = 1;
            if (getCheckAt(row, col) == player)
            {
                if (row != 0 && getCheckAt(row - 1, col) == -player)
                    first = true;
                _winningPoints.push_back(_pArr[row][col]);
                for (int k = row + 1; k - row + 1 <= max; k++)
                {
                    if (getCheckAt(k, col) == getCheckAt(row, col))
                    {
                        count++;
                        _winningPoints.push_back(_pArr[k][col]);
                    }
                    else
                    {
                        row = k;
                        break;
                    }
                }
                if (row + max < _size && count == max && getCheckAt(row + max, col) == -player)
                    last = true;

                if (count == max && (first == false || last == false))
                    return true;
                else
                    resetWinningPoints();
            }
        }
    }
    return false;
}
bool _Board::checkLeftCross(int max, int player)
{
    bool first = false, last = false;
    for (int row = 0; row < _size - max + 1; row++)
    {
        for (int col = _size - 1; col >= max - 1; col--)
        {
            first = false, last = false;
            if (getCheckAt(row, col) == player)
            {
                if (row != 0 && col != _size - 1 && getCheckAt(row - 1, col + 1) == -player)
                    first = true;
                _winningPoints.push_back(_pArr[row][col]);
                int count = 1;
                int i = row, j = col;
                while (count < max)
                {
                    i++;
                    j--;
                    if (getCheckAt(i, j) == getCheckAt(row, col))
                    {
                        count++;
                        _winningPoints.push_back(_pArr[i][j]);
                    }
                    else
                        break;
                }
                if (count == max && row+max < _size && col-max>=0 && getCheckAt(row + max, col - max) == -player)
                    last = true;

                if (count == max && (first == false || last == false))
                    return true;
                else
                    resetWinningPoints();
            }
        }
    }
    return false;
}
bool _Board::checkRightCross(int max, int player)
{
    bool first = false, last = false;
    for (int row = 0; row < _size - max + 1; row++)
    {
        for (int col = 0; col < _size - max + 1; col++)
        {
            first = false, last = false;
            if (getCheckAt(row, col) == player)
            {
                if (row != 0 && col != 0 && getCheckAt(row - 1, col - 1) == -player)
                    first = true;
                _winningPoints.push_back(_pArr[row][col]);
                int count = 1;
                int i = row, j = col;
                while (count < max)
                {
                    i++;
                    j++;
                    if (getCheckAt(i, j) == getCheckAt(row, col))
                    {
                        count++;
                        _winningPoints.push_back(_pArr[i][j]);
                    }
                    else
                        break;
                }
                if (count == max && row + max < _size && col + max < _size && getCheckAt(row + max, col + max) == -player)
                    last = true;

                if (count == max && (first == false || last == false))
                    return true;
                else
                    resetWinningPoints();
            }
        }
    }
    return false;
}
int _Board::testBoard(bool turn) //if current turn player win, return -1, drawn return 0, no one win return 2
{
    //max row of icons to win, max = size if size < 5, max = 5 if size >=5
    int max = (_size < 5) ? _size : 5;
    //Return player from turn//turn == true -> player = -1, turn == false -> player = 1
    int player = (turn == true) ? -1 : 1;
    //if player win
    if (checkRows(max, player) || checkCols(max, player) || checkRightCross(max, player) || checkLeftCross(max,player))
        return -1;
    //if they drawn
    if (_numPlayer1 + _numPlayer2 == _size*_size)
        return 0;
    //if no one win
    return 2;
}
