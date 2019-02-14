#include "Caro.h"
#include "Random.h"
#include "ConsoleWindow.h"
#include <Windows.h>
#include <iostream>
using namespace std;
#include <thread>
int main()
{
    _Common::resizeFont(24);
    SetConsoleTitle(TEXT("Caro"));
    _Common::resizeConsole(980, 740);
    _Common::fixConsoleWindow();
    Random r;
    Caro c;
    c.run();
    return 0;
}