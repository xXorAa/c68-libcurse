#include "curses.h"
#include "screen.h"

int
slk_attron(chtype attr)
{
  return(wattron(_screen->_slkscr,attr));
}
