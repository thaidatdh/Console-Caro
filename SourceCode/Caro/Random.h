#pragma once
#include <time.h>
#include <stdlib.h>
class Random
{
public:
    Random();
    static int Next();
    static int Next(int max);
};