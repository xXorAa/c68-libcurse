#include "curses.h"

int
instr(char *str)
{
  return(winnstr(stdscr,str,-1));
}
