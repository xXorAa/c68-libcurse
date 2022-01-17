#include "curses.h"

int
standend(void)
{
  return(wstandend(stdscr));
}
