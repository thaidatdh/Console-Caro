#pragma once
class _Common
{
private: 
    static bool _isSound;
public:
    static bool GetAudioStatus() { return _isSound; }
public:
    static void fixConsoleWindow();
    static void gotoXY(int ptX, int ptY);
    static void DrawRect(int x, int y, int width, int height, int curPosX=0, int curPosY=0); //draw rectangle
    static void drawSeparatingHorizontalLine(int x, int y, int length); //draw separating line of retangle
    static void setTextColor(int x);
    static void resizeConsole(int width, int height);
    static void resizeFont(int size);
    static void playSound(int i);
    static void ReverseAudioStatus();
};
class _DrawCharacter
{
public:
    static void drawA(int x, int y, int color);
    static void drawX(int x, int y, int color);
    static void drawO(int x, int y, int color);
    static void drawD(int x, int y, int color);
    static void drawR(int x, int y, int color);
    static void drawW(int x, int y, int color);
    static void drawN(int x, int y, int color);
};