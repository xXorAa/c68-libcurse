#include "curses.h"

int
getch(void)
{
  return(wgetch(stdscr));
}
