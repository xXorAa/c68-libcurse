#include "curses.h"

void
bkgdset(chtype ch)
{
  wbkgdset(stdscr,ch);
}
