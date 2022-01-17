#include "curses.h"

int
erase(void)
{
  return(werase(stdscr));
}
