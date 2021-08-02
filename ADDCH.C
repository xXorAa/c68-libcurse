#include "curses.h"

int
addch(chtype ch)
{
  return(waddch(stdscr,ch));
}
