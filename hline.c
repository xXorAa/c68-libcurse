#include "curses.h"

int
hline(chtype ch, int n)
{
  return(whline(stdscr,ch,n));
}
