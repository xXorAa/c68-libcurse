#include "curses.h"

/*
AT&T A series of calls to wgetch() are made, until a newline, carrage
AT&T returns, or enter key is recieved.  The resulting value (except
AT&T for this termination character) is placed in the area pointed at
AT&T by the characters pointer str.
AT&T The user's erase and kill characters are interpreted as well as
AT&T any special keys (such as function keys, "home" key, "clear" key,
AT&T etc).  At most n characters are read, thus preventing a possible
AT&T overflow of the input buffer.
*/

int
wgetnstr(WINDOW *win, char *str, int n)
{
  int ch;

  if(win == 0 || str == 0) return(ERR);

  while(n--)
    {
    switch(ch = wgetch(win))
      {
    case '\n' :
    case '\r' :
    case KEY_ENTER :
    case EOF :
      n = 0; /* terminate loop */
      break;
    default :
      *str++ = ch;
      }
    }
  *str = '\0';
  return(OK);
}
