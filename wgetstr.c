#include "curses.h"

/*
AT&T A series of calls to wgetch() are made, until a newline, carrage
AT&T returns, or enter key is recieved.  The resulting value (except
AT&T for this termination character) is placed in the area pointed at
AT&T by the characters pointer str.
AT&T The user's erase and kill characters are interpreted as well as any
AT&T special keys (such as function keys, "home" key, "clear" key, etc).
*/

int
wgetstr(WINDOW *win, char *str)
{
  return(wgetnstr(win, str, -1));
}
