#include "curses.h"

int
clear(void)
{
  return(wclear(stdscr));
}
