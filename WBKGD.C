#include "curses.h"
#include "window.h"

/*AT&T
AT&T The wbkgd() routine combines the new background with every position
AT&T in the window.  Background is any combination of attributes and a
AT&T character.  Only the attribute part is used to set the background
AT&T of non-blank characters, while both character and attributes are
AT&T used for blank positions.  To the extent possible on a particular
AT&T terminal, the attribute part of the background is displayed as the
AT&T graphic rendition of the character put on the screen.
AT&T */

int
wbkgd(WINDOW *win, chtype ch)
{
  _LINE *ystart, *yend;
  int cols;

  if(win == 0) return(ERR);

  ystart = win->_lines;
  yend = ystart + win->_rows;
  cols = win->_cols;
  for(; ystart != yend; ystart++)
    {
    chtype *xstart = ystart->line;
    chtype *xend = xstart + cols;
    for(; xstart != xend; xstart++)
      {
      *xstart = ((*xstart & A_CHARTEXT) == ' ') ? ch : 
                ((*xstart & A_CHARTEXT) | (ch & A_ATTRIBUTES));
      }
    }
  return(OK);
}
