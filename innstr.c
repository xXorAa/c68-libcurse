#include "curses.h"

int
innstr(char *str, int n)
{
  return(winnstr(stdscr,str,n));
}
