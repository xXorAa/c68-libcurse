#include "curses.h"

int
attrset(chtype attrs)
{
  return(wattrset(stdscr,attrs));
}
