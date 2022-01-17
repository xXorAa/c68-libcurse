#include "curses.h"

int
refresh(void)
{
  return(wrefresh(stdscr));
}
