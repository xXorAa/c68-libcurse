#include "curses.h"

/*
AT&T This routine writes all the characters of the NULL terminated
AT&T character string str on the given window.
AT&T It is similar to calling waddch once for each character in the string.
AT&T It will write at most n characters.
AT&T If n is negative, then the entire string will be added.
*/

int
waddnstr(WINDOW *win, char *str, int n)
{
  if(win == 0) return(ERR);

  if(n < 0) n = 999;
  for(; n && *str ; n--) (void) waddch(win, (chtype) *str++);
  return(OK);
}
