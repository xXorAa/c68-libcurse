#include "curses.h"
#include "window.h"

/*AT&T
AT&T With the putwin() routine, all data associated with window
AT&T win is written into the file to which filep points.
AT&T This information can be later retrieved using the getwin() routine.
AT&T */

int
putwin(WINDOW *win, FILE *filep)
{
  _LINE *ystart, *yend;
  int linesz = sizeof(chtype) * win->_cols;

  if(win == 0 || filep == 0) return(ERR);

  if(fwrite((char *)win, sizeof(WINDOW), 1, filep) != sizeof(WINDOW))
    return(ERR);
  ystart = win->_lines;
  yend = ystart + win->_rows;
  for(; ystart != yend; ystart++)
    {
    if(fwrite((char *)ystart->line, linesz, 1, filep) != linesz) return(ERR);
    }
  return(OK);
}
