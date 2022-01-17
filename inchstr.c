#include "curses.h"

int
inchstr(chtype *chstr)
{
  return(winchnstr(stdscr,chstr,-1));
}
