#include "curses.h"

int
vwprintw(WINDOW *win, char *fmt, va_list arg)
{
  char buf[BUFSIZ];

  (void)vsprintf(buf,fmt,arg);

  return(waddstr(win,buf));
}
