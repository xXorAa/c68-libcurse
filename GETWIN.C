#include <stdlib.h>
#include "curses.h"
#include "window.h"
#include "privfunc.h"

/*AT&T
AT&T The getwin() routine reads window related data stored in the file
AT&T by putwin().  The routine then creates and initialises a new window
AT&T using that data.  It returns a pointer to the new window.
AT&T */

WINDOW *
getwin(FILE *filep)
{
  WINDOW *win, fwin;
  _LINE *ystart, *yend;
  int linesz;

  if(filep == 0) return((WINDOW*)0);
  if(fread((char*)&fwin, sizeof(WINDOW), 1, filep) != sizeof(WINDOW))
    return((WINDOW*)0);;
  win = _mallocwindow(fwin._rows,fwin._cols,FALSE);
  if(win==(WINDOW*)0) return((WINDOW*)0);

  *win = fwin;
  win->_parent = 0;
  win->_children = 0;

  ystart = win->_lines;
  yend = ystart + win->_rows;
  linesz = sizeof(chtype)*win->_cols;
  for(; ystart != yend; ystart++)
    {
    if(fread((char *)ystart->line, linesz, 1, filep) != sizeof(WINDOW))
      {
      free(win);
      return((WINDOW*)0);
      }
    }
  (void)touchwin(win);
  return(win);
}

