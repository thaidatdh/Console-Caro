#include "Caro.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Game.h"
#include <thread>
void Caro::drawCaroLogo()
{
    //Draw Logo
    _Common::gotoXY(23, 1);
    cout << "  _____               _____      ____";
    _Common::gotoXY(23, 2);
    cout << " /     \\      /\\     |     \\    /    \\";
    _Common::gotoXY(23, 3);
    cout << "|            /  \\    |      |  |      |";
    _Common::gotoXY(23, 4);
    cout << "|           /    \\   |_____/   |      |";
    _Common::gotoXY(23, 5);
    cout << "|          |______|  |     \\   |      |";
    _Common::gotoXY(23, 6);
    cout << "|          |      |  |      \\  |      |";
    _Common::gotoXY(23, 7);
    cout << " \\_____/   |      |  |       \\  \\____/";
}
void Caro::drawMainInterface()
{
    system("cls");
    //Big screen
    _Common::setTextColor(11); //Set light aqua color
    _Common::DrawRect(20, 0, 44, 22); 
    _Common::gotoXY(40, 0);
    cout << " Caro \n\n";
    //draw logo
    drawCaroLogo();
    //
    _Common::setTextColor(3); //Set light blue color
    //New game:
    _Common::DrawRect(30, 9, 24, 2);
    _Common::gotoXY(38, 10);
    cout << "New game\n";
    //Load game:
    _Common::DrawRect(30, 12, 24, 2);
    _Common::gotoXY(38, 13);
    cout << "Load game\n";
    //Setting:
    _Common::DrawRect(30, 15, 24, 2);
    _Common::gotoXY(39, 16);
    cout << "Setting\n";
    //Exit:
    _Common::DrawRect(30, 18, 24, 2);
    _Common::gotoXY(40, 19);
    cout << "Exit\n";
}
void Caro::drawModeChoices()
{
    system("cls");
    //Big screen
    _Common::setTextColor(11); //Set light aqua color
    _Common::DrawRect(20, 0, 44, 22);
    _Common::gotoXY(37, 0);
    printf(" Caro : Mode \n\n");
    //draw logo
    drawCaroLogo();
    //
    _Common::setTextColor(3); //Set light blue color
                              //single player
    _Common::DrawRect(30, 9, 24, 2);
    _Common::gotoXY(39, 10);
    printf("1 Player\n");
    //double player
    _Common::DrawRect(30, 12, 24, 2);
    _Common::gotoXY(39, 13);
    printf("2 Players\n");
    //Back
    _Common::DrawRect(30, 15, 24, 2);
    _Common::gotoXY(41, 16);
    printf("Back\n");
}
void Caro::drawBoardChoices()
{
    system("cls");
    //Big screen
    _Common::setTextColor(11); //Set light aqua color
    _Common::DrawRect(20, 0, 44, 22);
    _Common::gotoXY(33, 0);
    printf(" Caro : Board Size \n\n");
    //draw logo
    drawCaroLogo();
    //
    _Common::setTextColor(3); //Set light blue color
                              //3x3 board
    _Common::DrawRect(30, 9, 24, 2);
    _Common::gotoXY(40, 10);
    printf("3 x 3\n");
    //5x5 board
    _Common::DrawRect(30, 12, 24, 2);
    _Common::gotoXY(40, 13);
    printf("5 x 5\n");
    //10x10 board
    _Common::DrawRect(30, 15, 24, 2);
    _Common::gotoXY(39, 16);
    printf("10 x 10\n");
    //Back
    _Common::DrawRect(30, 18, 24, 2);
    _Common::gotoXY(40, 19);
    printf("Back\n");
}
void Caro::drawSetting()
{
    system("cls");
    //Big screen
    _Common::setTextColor(11); //Set light aqua color
    _Common::DrawRect(20, 0, 44, 22);
    _Common::gotoXY(35, 0);
    printf(" Caro : Setting \n\n");
    //draw logo
    drawCaroLogo();
    //
    _Common::setTextColor(3); //Set light blue color
    //Audio setting
    _Common::DrawRect(30, 9, 24, 2);
    _Common::gotoXY(34, 10);
    if (_Common::GetAudioStatus() == true)
        printf("Audio:\tON\n");
    else
        printf("Audio:\tOFF\n");
    //back
    _Common::DrawRect(30, 12, 24, 2);
    _Common::gotoXY(40, 13);
    printf("Back\n");
}
void Caro::moveUp(int &command, int maxCommands)
{
    thread audioThread(_Common::playSound, 1);
    //draw old chosen button
    _Common::setTextColor(3);
    _Common::DrawRect(30, command * 3 + 6, 24, 2);
    //
    if (command == 1)
        command = maxCommands;
    else
        command -= 1;
    //draw new chosen button
    _Common::setTextColor(13);
    _Common::DrawRect(30, command * 3 + 6, 24, 2);
    _Common::setTextColor(3);
    audioThread.join();
}
void Caro::moveDown(int &command, int maxCommands)
{
    thread audioThread(_Common::playSound, 1);
    //draw old chosen button
    _Common::setTextColor(3);
    _Common::DrawRect(30, command * 3 + 6, 24, 2);
    //
    if (command == maxCommands)
        command = 1;
    else
        command += 1;
    //draw new chosen button
    _Common::setTextColor(13);
    _Common::DrawRect(30, command * 3 + 6, 24, 2);
    _Common::setTextColor(3);
    audioThread.join();
}
void Caro::initBoardLocation()
{
    LEFT = DEFAULT_LEFT;
    TOP = DEFAULT_TOP;
    switch (BOARD_SIZE)
    {
    case 3:
        LEFT += 15;
        TOP += 8;
        break;
    case 5:
        LEFT += 10;
        TOP += 6;
        break;
    default:
        TOP += 1;
        break;
    }
}
void Caro::startGame(int command)
{
    //init board location
    initBoardLocation();
    //Create a game
    _Game g(BOARD_SIZE, _isSingle, LEFT, TOP);
    if (command == 1)
    {
        g.startNewGame();
    }
    else
    {
        if (g.loadGame(1) == true)
        {
            g.startLoadedGame();
            if (g.getMode() == true && g.getTurn() == false)
            {
                g.moveToRandomLocation();
                g.processCheckBoard();
                g.processFinish();
            }
        }
        else
        {
            run(); //back the main menu
            return;
        }
    }
    //
    int whoWin = -1;
    while (g.isContinue())
    {
        g.waitKeyboard();
        if (g.getCommand() == 27) //esc key
        {
            g.breakGame();
            run();
        }
        else
        {
            switch (g.getCommand())
            {
            case 'A': case 75:
                g.moveLeft();
                break;
            case 'W': case 72:
                g.moveUp();
                break;
            case 'S': case 80:
                g.moveDown();
                break;
            case 'D': case 77:
                g.moveRight();
                break;
            case 'T':
                g.saveGame(2);
                break;
            case 'L':
                g.loadGame(2);
                g.startLoadedGame();
                break;
            case 32: //space key
            case 13: //enter key
                     //check the board and check if win/drawn/continue
                if (g.processCheckBoard())
                {
                    whoWin = g.processFinish();
                    switch (whoWin)
                    {
                    case -1: case 1: case 0:
                        if (g.askContinue() != 'Y')
                        {
                            g.exitGame();
                            run();
                        }
                        else
                            g.startGame();
                        break;
                    case 2:
                        break;
                    }
                }
                else
                    break;
                //if in single player mode, second player will auto check
                if (g.getMode() == true && whoWin != 0)
                {
                    g.moveToRandomLocation();
                    if (g.processCheckBoard())
                    {
                        whoWin = g.processFinish();
                        switch (whoWin)
                        {
                        case -1: case 1: case 0:
                            if (g.askContinue() != 'Y')
                            {
                                g.exitGame();
                                run();
                            }
                            else
                                g.startGame();
                            break;
                        case 2:
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
}
void Caro::setChoosedSizeBoard(int command)
{
    if (command == 1)
        BOARD_SIZE = 3;
    else if (command == 2)
        BOARD_SIZE = 5;
    else if (command==3)
        BOARD_SIZE = 10;
    else
    {
        //choose mode (1 player/2 players)
        chooseMode();
    }
}
void Caro::setChoosedMode(int command)
{
    if (command != 3)
    {
        if (command == 1)
            _isSingle = true;
        else if (command == 2)
            _isSingle = false;
        //choose board size (3/5/10)
        chooseSizeBoard();
    }
    //Come back main
    else
        run();
}
void Caro::setSettingCommand(int command)
{
    switch (command)
    {
    case 1:
        _Common::ReverseAudioStatus();
        Setting();
        break;
    default:
        run();
        break;
    }
}
void Caro::chooseSizeBoard()
{
    drawBoardChoices();
    int _size = getGameCommand(4);
    setChoosedSizeBoard(_size);
}
void Caro::chooseMode()
{
    //choose mode (1 player/2 players)
    drawModeChoices();
    int _mode = getGameCommand(3);
    setChoosedMode(_mode);
}
void Caro::Setting()
{
    drawSetting();
    int cmd = getGameCommand(2);
    setSettingCommand(cmd);
}
void Caro::executeMainCommand(int command)
{
    switch(command)
    {
    case 1://New Game
    {
        //choose mode (1 player/2 players)
        chooseMode();
        //start game
        startGame(1); 
    }
        break;
    case 2: //Load game
        startGame(2);
        break;
    case 3: //Setting
        Setting();
        break;
    case 4://Exit application
        _Common::gotoXY(25, 24);
        exit(0);
        break;
    }
}
int Caro::getGameCommand(int maxCommands)
{
    
    int cmd = 1;
    //set default choosen button
    _Common::setTextColor(13);
    _Common::DrawRect(30, 9, 24, 2);
    _Common::setTextColor(3);
    //
    bool isContinue = true;
    while (isContinue)
    {
        char key = toupper(_getch());
        switch (key)
        {
        case 'W': case 72:
            moveUp(cmd, maxCommands);
            break;
        case 'S': case 80:
            moveDown(cmd, maxCommands);
            break;
        case 27: //esc
        {
            thread audioThread(_Common::playSound, 0);
            cmd = maxCommands;
            isContinue = false; 
            audioThread.join();
        }
            break;
        case 13: //enter
        {
            thread audioThread(_Common::playSound, 0);
            isContinue = false;
            audioThread.join();
        }
            break;
        }
    }
    return cmd;
}
Caro::Caro()
{
    BOARD_SIZE = DEFAULT_SIZE;
    LEFT = DEFAULT_LEFT;
    TOP = DEFAULT_TOP;
    _isSingle = false;
}
void Caro::run()
{
    drawMainInterface();
    int cmd = getGameCommand(4);
    executeMainCommand(cmd);
}