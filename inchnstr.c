#include "curses.h"

int
inchnstr(chtype *chstr, int n)
{
  return(winchnstr(stdscr,chstr,n));
}
