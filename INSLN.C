#include "curses.h"

int
insertln(void)
{
  return(winsdelln(stdscr,1));
}
