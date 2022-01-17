#include "curses.h"

int
attron(chtype attrs)
{
  return(wattron(stdscr,attrs));
}
