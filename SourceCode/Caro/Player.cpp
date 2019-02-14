#include "Player.h"
_Player::_Player()
{
    _numChecked = 0;
    _winCount = 0;
}
void _Player::increaseNumChecked() 
{ 
    _numChecked++; 
}
void _Player::increaseWinCount() 
{ 
    _winCount++; 
}
void _Player::resetNumChecked()
{
    _numChecked = 0;
}
void _Player::resetWinCount()
{
    _winCount = 0;
}