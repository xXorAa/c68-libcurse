#include "curses.h"

/*AT&T
AT&T The virtual screen is set to the contents of filename,
AT&T which must have been written using scr_dump().
AT&T ERR is returned if the contents of filename are not
AT&T compatible with the current release of curses software.
AT&T The next call to doupdate() will restore the screen to
AT&T what it looked like in the dump file.
AT&T */

int
scr_restore(char *filename)
{
  WINDOW *win;
  FILE *fd;

  if(filename == 0) return(ERR);

  if((fd = fopen (filename, "r")) == NULL) return(ERR);
  if((win = getwin (fd)) == 0)
    {
    (void)delwin(curscr);
    curscr = win;
    }
  (void)fclose(fd);
  return(OK);
}
