#include "curses.h"

int
insdelln(int n)
{
  return(winsdelln(stdscr,n));
}
