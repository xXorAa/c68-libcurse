#include "curses.h"

int
getstr(char *str)
{
  return(wgetnstr(stdscr, str, -1));
}
