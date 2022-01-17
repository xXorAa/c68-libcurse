#include "curses.h"

int
clrtoeol(void)
{
  return(wclrtoeol(stdscr));
}
