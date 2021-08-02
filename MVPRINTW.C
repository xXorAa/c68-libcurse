#include "curses.h"

/*AT&T
AT&T These routines are analogous to fprintf().  The string which would be
AT&T output by fprintf() is instead output using waddstr() on the given
AT&T window.
AT&T */

int
mvprintw(int y, int x, char *fmt, ...) 
{
  char buf[BUFSIZ];
  register va_list arg;

  va_start(arg,fmt);
  (void)vsprintf(buf,fmt,arg);
  va_end(arg);

  return(mvaddstr(y,x,buf));
}
