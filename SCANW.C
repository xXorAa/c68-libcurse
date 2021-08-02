#include "curses.h"
#include "privfunc.h"

int
scanw(char *format, ...)
{
  char string[BUFSIZ];    /* source of data */
  int n;
  va_list ap;

  if(getstr(string)==ERR) return(ERR);
  va_start(ap,format);
  n = _vsscanf(string,format,ap);
  va_end(ap);
  return (n);
}
