#include "curses.h"

int
mvaddch(int y, int x, chtype ch)
{
  if(wmove(stdscr,y,x)==ERR) return(ERR);
  return(waddch(stdscr,ch));
}
