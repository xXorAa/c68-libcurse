#include "curses.h"
#include "privfunc.h"

int
wscanw(WINDOW *win, char *format, ...)
{
  char string[BUFSIZ];    /* source of data */
  int n;
  va_list arg;

  if(wgetstr(win,string)==ERR) return(ERR);
  va_start(arg,format);
  n = _vsscanf(string,format,arg);
  va_end(arg);
  return(n);
}
