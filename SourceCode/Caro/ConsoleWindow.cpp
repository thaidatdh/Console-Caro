#include "ConsoleWindow.h"
#include <Windows.h>
#include <cwchar>
#include <iostream>
#include <mmsystem.h>
#include <thread>
#pragma comment(lib, "winmm.lib")
using namespace std;
bool _Common::_isSound = true;
void _Common::ReverseAudioStatus() 
{ 
    _isSound = !_isSound;
}
void _Common::gotoXY(int ptX, int ptY)
{
    COORD coord;
    coord.X = ptX;
    coord.Y = ptY;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void _Common::fixConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
/*
*This method draws the rectangle.
*Usage:
*DrawRect(1, 1, 10, 10); or DrawRect(1, 1, 10, 10, 20, 5);
//Reference: https://www.codeproject.com/Tips/242879/Cplusplus-Drawing-Rectangles-to-Console
*/
void _Common::DrawRect(int x, int y, int width, int height, int curPosX, int curPosY)
{
    _Common::gotoXY(x, y); cout << char(201);
    for (int i = 1; i < width; i++)cout << char(205);
    cout << char(187);
    _Common::gotoXY(x, height + y); cout << char(200);
    for (int i = 1; i < width; i++)cout << char(205);
    cout << char(188);
    for (int i = y + 1; i < height + y; i++)
    {
        _Common::gotoXY(x, i); cout << char(186);
        _Common::gotoXY(x + width, i); cout << char(186);
    }
    _Common::gotoXY(curPosX, curPosY);
}
void _Common::drawSeparatingHorizontalLine(int x, int y, int length) //draw separating line of retangle
{
    _Common::gotoXY(x, y);
    cout << char(204);
    for (int i = 1; i <= length - 1; i++)
        cout << char(205);
    cout << char(185);
}
//reference: https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
void _Common::setTextColor(int x)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}
//reference: http://www.cplusplus.com/forum/beginner/1481/
void _Common::resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT rect;
    GetWindowRect(console, &rect);
    MoveWindow(console, rect.left, rect.top, width, height, TRUE);
}
//reference: https://stackoverflow.com/questions/35382432/how-to-change-the-console-font-size
void _Common::resizeFont(int size)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 24;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
//play sound
//reference: https://docs.microsoft.com/en-us/previous-versions/dd743680(v%3Dvs.85)
//0 is enter sound
//1 is switch sound
//2 is win/draw sound
void _Common::playSound(int i)
{
    if (_Common::GetAudioStatus() == true)
    {
        switch (i)
        {
        case 0:
            PlaySound(TEXT("Audio\\enter.wav"), NULL, SND_FILENAME);
            break;
        case 1:
            PlaySound(TEXT("Audio\\switch.wav"), NULL, SND_FILENAME);
            break;
        case 2:
            PlaySound(TEXT("Audio\\win.wav"), NULL, SND_FILENAME);
            break;
        }
    }
}
//draw characters
void _DrawCharacter::drawX(int x, int y, int color)
{
    _Common::setTextColor(color);
    _Common::gotoXY(x, y);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 1);
    cout << " " << char(219) << " " << char(219) << " ";
    _Common::gotoXY(x, y + 2);
    cout << " " << " " << char(219) << " ";
    _Common::gotoXY(x, y + 3);
    cout << " " << char(219) << " " << char(219) << " ";
    _Common::gotoXY(x, y + 4);
    cout << char(219) << " " << " " << " " << char(219);
}
void _DrawCharacter::drawW(int x, int y, int color)
{
    _Common::setTextColor(color);
    _Common::gotoXY(x, y);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 1);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 2);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 3);
    cout << char(219) << " " << char(219) << " " << char(219);
    _Common::gotoXY(x, y + 4);
    cout << " " << char(219) << " " << char(219);
}
void _DrawCharacter::drawO(int x, int y, int color)
{
    _Common::setTextColor(color);
    _Common::gotoXY(x, y);
    cout << " " << char(219) << char(219) << char(219);
    _Common::gotoXY(x, y + 1);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 2);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 3);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 4);
    cout << " " << char(219) << char(219) << char(219);
}
void _DrawCharacter::drawN(int x, int y, int color)
{
    _Common::setTextColor(color);
    _Common::gotoXY(x, y);
    cout << char(219) << char(219) << " " << " " << char(219);
    _Common::gotoXY(x, y + 1);
    cout << char(219) << " " << char(219) << " " << char(219);
    _Common::gotoXY(x, y + 2);
    cout << char(219) << " " << " " << char(219) << char(219);
    _Common::gotoXY(x, y + 3);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 4);
    cout << char(219) << " " << " " << " " << char(219);
}
void _DrawCharacter::drawA(int x, int y, int color)
{
    _Common::setTextColor(color);
    _Common::gotoXY(x, y);
    cout << " " << char(219) << char(219) << char(219);
    _Common::gotoXY(x, y + 1);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 2);
    cout << char(219) << char(219) << char(219) << char(219) << char(219);
    _Common::gotoXY(x, y + 3);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 4);
    cout << char(219) << " " << " " << " " << char(219);
}
void _DrawCharacter::drawD(int x, int y, int color)
{
    _Common::setTextColor(color);
    _Common::gotoXY(x, y);
    cout << char(219) << char(219) << char(219);
    _Common::gotoXY(x, y + 1);
    cout << char(219) << " " << " " << char(219);
    _Common::gotoXY(x, y + 2);
    cout << char(219) << " " << " " << " " << char(219);
    _Common::gotoXY(x, y + 3);
    cout << char(219) << " " << " " << char(219);
    _Common::gotoXY(x, y + 4);
    cout << char(219) << char(219) << char(219);
}
void _DrawCharacter::drawR(int x, int y, int color)
{
    _Common::setTextColor(color);
    _Common::gotoXY(x, y);
    cout << char(219) << char(219) << char(219);
    _Common::gotoXY(x, y + 1);
    cout << char(219) << " " << " " << char(219);
    _Common::gotoXY(x, y + 2);
    cout << char(219) << char(219) << char(219);
    _Common::gotoXY(x, y + 3);
    cout << char(219) << " " << char(219);
    _Common::gotoXY(x, y + 4);
    cout << char(219) << " " << " " << char(219);
}