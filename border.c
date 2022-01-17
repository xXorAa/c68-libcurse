#include "curses.h"

int
border(chtype ls, chtype rs, chtype ts, chtype bs,
        chtype tl, chtype tr, chtype bl, chtype br)
{
  return(wborder(stdscr,ls,rs,ts,bs,tl,tr,bl,br));
}
