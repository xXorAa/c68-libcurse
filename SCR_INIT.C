#include "curses.h"
#include "screen.h"

/*AT&T
AT&T The contents of filename are read in and used to initialise the
AT&T curses data structures about what the terminal currently has on
AT&T its screen.  If the data is determined to be valid, curses will
AT&T base its next update of the screen on the information rather than
AT&T clearing the screen and starting from scratch.  scr_init() would be
AT&T used after initscr() or a system() call to share the screen with
AT&T another process which has done a scr_dump() after its endwin().
AT&T The data will be declared invalid if the terminfo capability nrrmc
AT&T is TRUE or the time-stamp of the tty is OLD.  Note that keypad(),
AT&T meta(), slk_clear(), curs_set(), flash(), and beep() do not affect
AT&T the contents of the screen, but will make the tty's time-stamp old.
AT&T */

int
scr_init(char *filename)
{
  WINDOW *win;
  FILE *fd;

  if(filename == 0 || _screen == 0) return(ERR);

  if((fd = fopen (filename, "r")) == NULL) return(ERR);

  if((win=getwin(fd)) != 0)
    {
    (void)delwin(_screen->_physcr);
    _screen->_physcr = win;
    }
  (void)fclose(fd);
  return(OK);
}
