#include "curses.h"

int
delch(void)
{
  return(wdelch(stdscr));
}
