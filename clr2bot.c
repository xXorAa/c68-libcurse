#include "curses.h"

int
clrtobot(void)
{
  return(wclrtobot(stdscr));
}
