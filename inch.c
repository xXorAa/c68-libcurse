#include "curses.h"

chtype
inch(void)
{
  return(winch(stdscr));
}
