#include "curses.h"

int
insnstr(char *str, int n)
{
  return(winsnstr(stdscr,str,n));
}
