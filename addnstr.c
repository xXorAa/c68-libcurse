#include "curses.h"

int
addnstr(char *s, int n)
{
  return(waddnstr(stdscr,s,n));
}
