#include "Random.h"
Random::Random()
{
    srand(time(NULL));
}
int Random::Next()
{
    return rand();
}
int Random::Next(int max)
{
    return Next() % max;
}