#include "curses.h"

int
mvwprintw(WINDOW *win, int y, int x, char *fmt, ...)
{
  char buf[BUFSIZ];
  register va_list arg;

  va_start(arg,fmt);
  (void)vsprintf(buf,fmt,arg);
  va_end(arg);

  return(mvwaddstr(win,y,x,buf));
}
