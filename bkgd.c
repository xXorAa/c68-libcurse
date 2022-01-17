#include "curses.h"

int
bkgd(chtype ch)
{
  return(wbkgd(stdscr,ch));
}
