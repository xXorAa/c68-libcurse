#include "curses.h"

int
echochar(chtype ch)
{
  return(wechochar(stdscr,ch));
}
