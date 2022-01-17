#include "curses.h"
#include "privfunc.h"

/*AT&T
AT&T These routines corresponds to scanf().  wgetstr() is called on
AT&T the window, and the resulting line is used as input for the scan.
AT&T The return value for this routine is the number of arg values that
AT&T are converted by format.
AT&T arg values that are not converted are lost.
AT&T */

int
mvscanw(int y, int x, char *format, ...)
{
  char string[BUFSIZ];    /* source of data */
  int n;

  if(mvgetstr(y,x,string)==ERR) return(ERR);
  {
  va_list ap;
  va_start(ap,format);
  n = _vsscanf(string,format,ap);
  va_end(ap);
  }
  return(n);
}
