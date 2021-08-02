#include "curses.h"

int
addchnstr(chtype *chstr, int n)
{
  return(waddchnstr(stdscr,chstr,n));
}
