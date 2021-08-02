#include "curses.h"
#include "privfunc.h"

int
vwscanw(WINDOW *win, char *format, va_list ap)
{
  char string[BUFSIZ];    /* source of data */
  int n;

  if(wgetstr(win,string)==ERR) return(ERR);
  n = _vsscanf(string,format,ap);
  return(n);
}
