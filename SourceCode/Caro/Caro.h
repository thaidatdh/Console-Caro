#pragma once
#include "ConsoleWindow.h"
class Caro
{
private:
    const int DEFAULT_SIZE = 10;
    const int DEFAULT_LEFT = 30;
    const int DEFAULT_TOP = 2;
private:
    int BOARD_SIZE; //current game board size
    int LEFT;
    int TOP;
    bool _isSingle; //true: Single or false: Double player
public:
    int Left() { return LEFT; }
    int Top() { return TOP; }
private:
    void moveUp(int &command, int maxCommands);
    void moveDown(int &command, int maxCommands);
    void executeMainCommand(int command);
    void setChoosedMode(int command);
    void setChoosedSizeBoard(int command);
    void setSettingCommand(int command);
    void chooseMode();
    void chooseSizeBoard();
    void initBoardLocation();
    void drawSetting();
    void drawCaroLogo();
    void Setting();
public:
    void drawMainInterface();
    void drawModeChoices();
    void drawBoardChoices();
    int getGameCommand(int maxCommands);
    void startGame(int command);
    //
    void run();
public:
    Caro();
};