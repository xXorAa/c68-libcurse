#include "curses.h"
#include "privfunc.h"

int
mvwscanw(WINDOW *win, int y, int x, char *format, ...)
{
  char string[BUFSIZ];    /* source of data */
  int n;
  va_list ap;

  if(mvwgetstr(win,y,x,string)==ERR) return(ERR);
  va_start(ap,format);
  n = _vsscanf(string,format,ap);
  va_end(ap);
  return(n);
}
