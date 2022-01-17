#include "curses.h"
#include "screen.h"
#include "privfunc.h"

/*
This routine is an internal routine which reads the next
character from the input stream.
*/

int
_getchar(void)
{
  int ch;
  if(_screen->_chars_read)
    return(_screen->_chars[--(_screen->_chars_read)]);

  ch = fgetc(_screen->_infd);
  if(ch == -1) clearerr(_screen->_infd);
  return(ch);
}
