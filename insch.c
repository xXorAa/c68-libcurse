#include "curses.h"

int
insch(chtype ch)
{
  return(winsch(stdscr,ch));
}
