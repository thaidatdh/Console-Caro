#pragma once
#include "Board.h"
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
#include "Random.h"
#include "Player.h"
class _Game
{
private:
    _Board* _b; //a board
    bool _turn; //turn, true if player 1, false player 2
    int _x, _y; //x/y coordinate of the pointer
    int _command; //user's command from keyboard
    bool _loop; //true if the game is still continue
    bool _isSinglePlayer; //true: 1 Player, false: 2 player
    _Player _player1, _player2; //player info
public:
    int getCommand() { return _command; }
    bool isContinue() { return _loop; }
    bool getMode() { return _isSinglePlayer; }
    bool getTurn() { return _turn; }
private:
    void drawGameInfo();
    void updateTurnToInfoBox();
    //Draw game result
    //whoWin = -1 -> draw, whoWin = 1 -> X win, whoWin = 0 -> O win
    void drawGameResult(int whoWin);
public:
    char waitKeyboard();
    char askContinue();
    void startGame(); 
    void exitGame();
    void breakGame();
    int processFinish();
    bool processCheckBoard();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    //
    void moveToRandomLocation();
    //
    void saveGame(int mode);
    bool loadGame(int mode);
    //
    void startNewGame(); //function that start a new game
    void startLoadedGame(); //function that start a loaded game (load from a file)
public:
    _Game(int pSize, bool pMode, int pLeft, int pTop);
    ~_Game();
};