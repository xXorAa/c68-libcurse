#include "curses.h"

int
insstr(char *str)
{
  return(winsnstr(stdscr,str,-1));
}
