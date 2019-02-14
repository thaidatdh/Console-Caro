#include "Game.h"
#include <thread>
_Game::_Game(int pSize, bool pMode, int pLeft, int pTop)
{
    _b = new _Board(pSize, pLeft, pTop);
    _loop = _turn = true;
    _command = -1;
    _x = pLeft;
    _y = pTop;
    _isSinglePlayer = pMode;
    
}
_Game::~_Game()
{
    delete _b;
}
char _Game::waitKeyboard()
{
    _command = toupper(_getch());
    return _command;
}
char _Game::askContinue()
{
    //may save the game before exit
    _Common::setTextColor(7);
    _Common::gotoXY(1, 27);
    cout<< "Do you want to continue playing? (Y/N)";
    return waitKeyboard();
}
#include <iomanip>
void _Game::drawGameInfo()
{
    //Big screen
    _Common::setTextColor(11); //Set light aqua color
    _Common::DrawRect(0, 0, 83, 26);
    _Common::gotoXY(40, 0);
    cout << " Caro ";
    //draw notification box
    _Common::setTextColor(11); //light aqua color
    _Common::DrawRect(0, 26, 83, 2);
    _Common::drawSeparatingHorizontalLine(0, 26, 83);
    _Common::gotoXY(1, 26);
    cout << "Notification";
    //Info box
    _Common::setTextColor(14); //light yellow
    _Common::DrawRect(1, 1, 16, 24);
    _Common::gotoXY(4, 1);
    cout << "Information";
    //Draw board box
    _Common::setTextColor(14); ////light yellow
    _Common::DrawRect(18, 1, 63, 24);
    _Common::gotoXY(19, 1);
    cout << "Board";
    _Common::gotoXY(68, 1);
    if (_isSinglePlayer == true)
        cout << "Single Player";
    else
        cout << "Double Player";
    //reset to white
    _Common::setTextColor(7);
    //write game's info
    //these four print player name
    _Common::gotoXY(3, 2);
    _Common::setTextColor(6);
    cout << "Player ";
    _Common::setTextColor(4);
    cout << "X";
    //print player X info
    _Common::setTextColor(7);
    _Common::gotoXY(3, 3);
    cout << "+ Win: " << _player1.getWinCount();
    _Common::gotoXY(3, 4);
    cout << "+ Checked: " << _player1.getNumChecked();
    //these four print player name
    _Common::gotoXY(3, 6);
    _Common::setTextColor(6);
    cout << "Player ";
    _Common::setTextColor(11);
    cout<< "O";
    _Common::setTextColor(7);
    //print player O info
    _Common::gotoXY(3, 7);
    cout << "+ Win: " << _player2.getWinCount();
    _Common::gotoXY(3, 8);
    cout << "+ Checked: " << _player2.getNumChecked();
    //Print new seprate line
    _Common::setTextColor(14); //light yellow
    _Common::drawSeparatingHorizontalLine(1, 10, 16);
    //Print key instruction text
    _Common::gotoXY(6, 10);
    cout << "Keyboard";
    _Common::setTextColor(2);
    _Common::gotoXY(3, 11);
    cout << "    A = Left";
    _Common::gotoXY(3, 12);
    cout << "    D = Right";
    _Common::gotoXY(3, 13);
    cout << "    W = Up";
    _Common::gotoXY(3, 14);
    cout << "    S = Down";
    _Common::setTextColor(9);
    _Common::gotoXY(3, 15);
    cout << "Enter : Check";
    _Common::setTextColor(4);
    _Common::gotoXY(3, 16);
    cout << "  ESC : Quit";
    _Common::gotoXY(3, 17);
    cout << "    T : Save";
    _Common::gotoXY(3, 18);
    cout << "    L : Load";
    //Print new seprate line
    _Common::setTextColor(14); //light yellow
    _Common::drawSeparatingHorizontalLine(1, 19, 16);
    //Print turn box
    _Common::gotoXY(8, 19);
    cout << "Turn";
    //Print Current turn
    if (_turn == true)
        _DrawCharacter::drawX(7, 20, 4);
    else
        _DrawCharacter::drawO(7, 20, 11);
    //reset to white
    _Common::setTextColor(7);
}
void _Game::startGame() //start game function
{
    system("cls");
    _b->resetData(); //init board's data
    _player1.resetNumChecked();
    _player2.resetNumChecked();
    drawGameInfo(); //draw game' info
    _b->drawData(); //draw the board
    _x = _b->getXAt(0, 0);
    _y = _b->getYAt(0, 0);
}
void _Game::startNewGame()
{
    startGame();
}
void _Game::startLoadedGame() //function that start a loaded game from file
{
    system("cls");
    _b->drawData(); //draw the board
    drawGameInfo(); //draw game's info
    _b->drawLoadedData(); //draw checked spot in the board
    _x = _b->getXAt(0, 0);
    _y = _b->getYAt(0, 0);
}
void _Game::saveGame(int mode)
{
    _Common::setTextColor(7);
    //clear old message
    _Common::gotoXY(1, 27);
    cout << "                                             ";
    //enter filename
    string str;
    _Common::gotoXY(1, 27);
    printf("Enter save file name: ");
    _Common::setTextColor(6);
    getline(cin, str);
    _Common::setTextColor(7);
    _Common::gotoXY(1, 27);
    const char* fileName = str.c_str();
    //open file and save data
    FILE* fo = NULL;
    fopen_s(&fo, fileName, "wb");
    if (fo != NULL)
    {
        //save info of 2 player
        fwrite(&_player1, sizeof(_Player), 1, fo);
        fwrite(&_player2, sizeof(_Player), 1, fo);
        //save mode (single/double)
        fwrite(&_isSinglePlayer, sizeof(_isSinglePlayer), 1, fo);
        //save turn
        fwrite(&_turn, sizeof(_turn), 1, fo);
        //save board's status
        _b->saveBoard(fo);
        if (mode != 1)
        {
            //clear old message
            _Common::gotoXY(1, 27);
            cout << "                                             ";
            //new message
            _Common::gotoXY(1, 27);
        }
        _Common::setTextColor(4);
        cout << "Saved into " << str << " file! ";
        if (mode == 1)
        {
            _Common::gotoXY(20, 27);
            _Common::setTextColor(7);
            cout << "Press any key to continue...";
        }
        else
        {
            _Common::gotoXY(_x, _y);
        }
    }
    else
    {
        //clear old message
        _Common::gotoXY(1, 27);
        cout << "                                             ";
        //new message
        _Common::setTextColor(4);
        cout << "Fail to save game! ";
        if (mode == 1)
        {
            _Common::gotoXY(20, 27);
            _Common::setTextColor(7);
            cout << "Press any key to continue...       ";
        }
        else
        {
            _Common::gotoXY(_x, _y);
        }
    }
    fclose(fo);
    _getch();
}
bool _Game::loadGame(int mode)
{
    //enter file name
    string str;
    if (mode == 1)
    {//Draw input box
        _Common::setTextColor(11); //Set light aqua color
        _Common::DrawRect(20, 23, 44, 2);
        _Common::gotoXY(21, 24);
    }
    else
    {
        _Common::gotoXY(1, 27);
    }
    //Write the requirement
    _Common::setTextColor(3); //Set light aqua color
    cout << "Enter filename: ";
    //Set white color
    _Common::setTextColor(7);
    getline(cin, str);
    const char* fileName = str.c_str();
    //open file and read
    FILE *fi = NULL;
    fopen_s(&fi, fileName, "rb");
    if (fi != NULL)
    {
        //Load info 2 player
        fread_s(&_player1, sizeof(_Player), sizeof(_Player), 1, fi);
        fread_s(&_player2, sizeof(_Player), sizeof(_Player), 1, fi);
        //load mode (single/double)
        fread_s(&_isSinglePlayer, sizeof(bool), sizeof(bool), 1, fi);
        //load turn
        fread_s(&_turn, sizeof(bool), sizeof(bool), 1, fi);
        //load board's status
        _b->loadBoard(fi);
        //clear old message
        _Common::gotoXY(1, 27);
        cout << "                                             ";
        //new message
        _Common::gotoXY(1, 27);
        cout << "Loaded from " << str << "!";
        _Common::gotoXY(_x, _y);
    }
    else 
    { 
        if (mode == 1)
            _Common::gotoXY(21, 24);
        else
        {
            //clear old message
            _Common::gotoXY(1, 27);
            cout << "                                             ";
            //new message
            _Common::gotoXY(1, 27);
        }
        _Common::setTextColor(4); //Set red color
        cout << "File " << str << " doesn't exist!";
        if (mode == 1)
            _getch();
        else
            _Common::gotoXY(_x, _y);
        return false;
    }
    fclose(fi);
    return true;
}
void _Game::exitGame() //exit game after finished the game
{
    //may save the game before exit
    _Common::setTextColor(7);
    _Common::gotoXY(1, 27);
    cout << "Do you want to save before exit? (Y/N)";
    //save if enter Y
    if (toupper(_getch()) == 'Y')
    {
        _player1.resetNumChecked();
        _player2.resetNumChecked();
        _b->resetData();
        saveGame(1);
    }
    _loop = false;
}
void _Game::breakGame() //exit in middle of the game
{
    //may save the game before exit
    _Common::setTextColor(7);
    _Common::gotoXY(1, 27);
    cout << "Do you want to save before exit? (Y/N)";
    //save if enter Y
    if (toupper(_getch()) == 'Y')
    {
        saveGame(1);
    }
    _loop = false;
}
void _Game::updateTurnToInfoBox()
{
    switch (_turn)
    {
    case 1:
        _DrawCharacter::drawX(7, 20, 0); //delete old turn icon
        _DrawCharacter::drawO(7, 20, 11);
        break;
    case 0:
        _DrawCharacter::drawO(7, 20, 0); //delete old turn icon
        _DrawCharacter::drawX(7, 20, 4);
        break;
    }
    _Common::setTextColor(7);
}
bool _Game::processCheckBoard()
{
    switch (_b->checkBoard(_x, _y, _turn))
    {
    case -1:
    {
        thread audioThread(_Common::playSound, 1);
        _Common::setTextColor(4);
        cout << "X";
        _player1.increaseNumChecked();
        //rewrite counting
        _Common::setTextColor(7); //white color
        _Common::gotoXY(14, 4);
        cout << _player1.getNumChecked();
        updateTurnToInfoBox();
        audioThread.join();
    }
    break;
    case 1:
    {
        thread audioThread(_Common::playSound, 1);
        _Common::setTextColor(11);
        cout << "O";
        _player2.increaseNumChecked();
        //rewrite counting
        _Common::setTextColor(7); //white color
        _Common::gotoXY(14, 8);
        cout << _player2.getNumChecked();
        updateTurnToInfoBox();
        audioThread.join();
    }
        break;
    case 0:
        return false; //if command check into a checked spot
    }
    return true;
}
int _Game::processFinish()
{
    int pWhoWin = _b->testBoard(_turn);
    
    switch (pWhoWin)
    {
    case -1: //win
        if (_turn == true)
        {
            drawGameResult(_turn);
            _player1.increaseWinCount();
        }
        else
        {
            drawGameResult(_turn);
            _player2.increaseWinCount();
        }
        _turn = !_turn;
        break;
    case 0: //drawn
        drawGameResult(-1);
        _turn = true;
        break;
    case 2: //no one win
        _turn = !_turn; //change turn
    }
    _Common::gotoXY(_x, _y);
    return pWhoWin;
}
void _Game::moveRight()
{
    if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
    {
        _x += 4;
        _Common::gotoXY(_x, _y);
    }
}
void _Game::moveLeft()
{
    if (_x > _b->getXAt(0, 0))
    {
        _x -= 4;
        _Common::gotoXY(_x, _y);
    }
}
void _Game::moveUp()
{
    if (_y > _b->getYAt(0, 0))
    {
        _y -= 2;
        _Common::gotoXY(_x, _y);
    }
}
void _Game::moveDown()
{
    if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
    {
        _y += 2;
        _Common::gotoXY(_x, _y);
    }
}
void _Game::moveToRandomLocation()
{
    int iC, jC;
    for (int i = 0; i < _b->getSize(); i++)
    {
        for (int j = 0; j < _b->getSize(); j++)
        {
            if (_b->getXAt(i, j) == _x && _b->getYAt(i, j) == _y)
            {
                iC = i;
                jC = j;
                i = j = _b->getSize();
            }
        }
    }
    int totalBlock = _b->getSize() * _b->getSize();
    int totalChecked = _player1.getNumChecked() + _player2.getNumChecked();
    do
    {
        int i = Random::Next(3);
        int j = Random::Next(3);
        switch (i)
        {
        case 0:
            if (iC > 0)
                iC -= 1;
            break;
        case 1:
            if (iC < _b->getSize() - 1)
                iC += 1;
            break;
        }
        switch (j)
        {
        case 0:
            if (jC > 0)
                jC -= 1;
            break;
        case 1:
            if (jC < _b->getSize() - 1)
            jC += 1;
            break;
        }
    } while (_b->getCheckAt(iC, jC) != 0 && totalChecked != totalBlock);
    _x = _b->getXAt(iC, jC);
    _y = _b->getYAt(iC, jC);
    _Common::gotoXY(_x, _y);
}

//Draw game result
//whoWin = -1 -> drawn, whoWin = 1 -> X win, whoWin = 0 -> O win
void _Game::drawGameResult(int whoWin)
{
    thread audioThread(_Common::playSound, 2);
    //draw result
    int color;
    int c=0;
    if (whoWin == -1)
    {
        do
        {
            //draw "draw"
            color = c + 1 <= 15 ? (c + 1) : (c + 1 - 15);
            _DrawCharacter::drawD(74, 2, color);
            color = c + 2 <= 15 ? (c + 2) : (c + 2 - 15);
            _DrawCharacter::drawR(74, 8, color);
            color = c + 3 <= 15 ? (c + 3) : (c + 3 - 15);
            _DrawCharacter::drawA(74, 14, color);
            color = c + 4 <= 15 ? (c + 4) : (c + 4 - 15);
            _DrawCharacter::drawW(74, 20, color);
            //draw players
            if (c % 2 == 1)
            {
                _DrawCharacter::drawX(22, 5, 4);
                _DrawCharacter::drawO(22, 15, 11);
            }
            else
            {
                _DrawCharacter::drawX(22, 5, 11);
                _DrawCharacter::drawO(22, 15, 4);
            }
            Sleep(200);
            c++;
        } while (c!=10);
    }
    else 
    {
        //draw "won"
        do
        {
            color = c + 1 <= 15 ? (c + 1) : (c + 1 - 15);
            _DrawCharacter::drawW(74, 4, color);
            color = c + 1 <= 15 ? (c + 2) : (c + 2 - 15);
            _DrawCharacter::drawO(74, 10, color);
            color = c + 1 <= 15 ? (c + 3) : (c + 3 - 15);
            _DrawCharacter::drawN(74, 16, color);
            //draw who won
            if (whoWin == 1) //X won
            {
                if (c % 2 == 1)
                    _DrawCharacter::drawX(22, 10, 4);
                else
                    _DrawCharacter::drawX(22, 10, 11);
            }
            else //O won
            {
                if (c % 2 == 1)
                    _DrawCharacter::drawO(22, 10, 11);
                else
                    _DrawCharacter::drawO(22, 10, 4);
            }
            //draw wining points
            int winSize = _b->_winningPoints.size();
            for (int i = 0; i < winSize; i++)
            {
                _Point a = _b->_winningPoints[i];
                if (c % 2 == 1)
                    _Common::setTextColor(10);
                else
                    _Common::setTextColor(13);
                _Common::gotoXY(a.getX(), a.getY());
                if (a.getCheck() == -1)
                    cout << "X";
                else if (a.getCheck() == 1)
                    cout << "O";
            }
            Sleep(200);
            c++;
        } while (c!=10);
    }
    _b->resetWinningPoints();
    audioThread.join();
    //reset color to white
    _Common::setTextColor(7);
}