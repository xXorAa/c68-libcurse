#include "curses.h"

int
standout(void)
{
  return(wstandout(stdscr));
}
