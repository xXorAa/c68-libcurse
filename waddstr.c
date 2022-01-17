#include "curses.h"

/*AT&T
AT&T This routine writes all the characters of the NULL-terminated
AT&T character string str on the given window.
AT&T This is equivalent to calling waddch() once for each
AT&T character in the string.
AT&T */

int
waddstr(WINDOW *win, char *str)
{
  char *s;

  if((win == 0) || (str == 0)) return(ERR);

  for(s = str; *s; s++) (void) waddch(win, (chtype) *s);
  return(OK);
}
