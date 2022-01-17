#include "curses.h"

int
deleteln(void)
{
  return(winsdelln(stdscr,-1));
}
