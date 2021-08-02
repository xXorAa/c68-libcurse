#include "curses.h"

int
addstr(char *str)
{
  return(waddstr(stdscr,str));
}
