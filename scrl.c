#include "curses.h"

int
scrl(int n)
{
  return(wscrl(stdscr,n));
}
