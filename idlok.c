#include "curses.h"
#include "term.h"
#include "window.h"

/*AT&T
AT&T With the idlok() routine, if enabled (bf is TRUE), curses conciders
AT&T using the hardware insert/delete line feature of terminals so equipped.
AT&T If disabled (bf is FALSE), curses very seldom uses this feature.
AT&T This option should be enabled only if the application needs
AT&T insert/delete line, for example, for a screen editor.
AT&T It is disabled be default because insert/delete line tends to be
AT&T visually annoying when used in applications where it isn't really
AT&T needed.  If insert/delete line cannot be used, curses redraws the
AT&T changed portions of all lines.
AT&T */

int
idlok(WINDOW *win, bool bf)
{
  if(win == 0) return(ERR);
  if(bf != 0 && delete_line != 0 && insert_line != 0) win->_flags |= F_ID;
  else win->_flags &= ~F_ID;
  return(OK);
}
