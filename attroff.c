#include "curses.h"

int
attroff(chtype attrs)
{
  return(wattroff(stdscr,attrs));
}
