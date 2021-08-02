#include "curses.h"
#include "window.h"

/*AT&T
AT&T The bkgdset routine manipulates the background of the named window.
AT&T Background is a chtype consisting of attributes and a character.
AT&T The attribute part of the background is combined (ORed) with all
AT&T non-blank characters that are written into the window with waddch().
AT&T Both the character and attribute parts of the background are
AT&T combined with the blank characters.
AT&T The background becomes a property of the character and moves with
AT&T the character through any scrolling and insert/delete line/character
AT&T operations.  To the extent possible on a particular terminal, the
AT&T attribute part of the background is displayed as the graphic
AT&T rendition of the character put on the screen.
AT&T */

void
wbkgdset(WINDOW *win, chtype ch)
{
  if(win != 0) win->_attr = ch;
}
