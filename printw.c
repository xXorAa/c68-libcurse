#include "curses.h"

int
printw(char *fmt, ...)
{
  char buf[BUFSIZ];
  register va_list arg;

  va_start(arg,fmt);
  (void)vsprintf(buf,fmt,arg);
  va_end(arg);

  return(addstr(buf));
}
