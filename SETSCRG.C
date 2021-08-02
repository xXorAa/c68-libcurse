#include "curses.h"

int
setscrreg(int top, int bot)
{
  return(wsetscrreg(stdscr,top,bot));
}
