#include <string.h>
#include "curses.h"
#include "screen.h"
#include "window.h"

/*AT&T
AT&T The scr_set() routine is a combination of scr_restore() and scr_init().
AT&T It tells the program that the information in filename is what is
AT&T currently on the screen, and also what the program wants on the screen.
AT&T This can be thought of as a screen inheritance function.
AT&T */

int
scr_set(char *filename)
{
  _LINE *ystart, *yend, *yptr;
  size_t len;

  if(_screen == 0 || scr_restore (filename) == ERR) return(ERR);

  len = sizeof(chtype) * curscr->_cols;
  yptr = _screen->_physcr->_lines,
  ystart = curscr->_lines;
  yend = ystart + curscr->_rows;
  for(; ystart != yend; ystart++, yptr++)
    {
    (void)memcpy((void *)yptr->line, (void *)ystart->line, len);
    }
  return(OK);
}
