#include <stdlib.h>
#include "curses.h"
#include "screen.h"
#include "privfunc.h"

static int _slkfmt = -1;

void _slk_init(void)
{
  int lab;
  if(_slkfmt < 0) return;
  LINES--;
  _screen->_slkscr = newwin(1, COLS, _screen->_stdbot--, 0);
  _screen->_slk_labels = (char *) calloc((size_t)8*9,sizeof(char));
  _screen->_slkfmt = _slkfmt;
  _slkfmt = -1;
  for(lab=1; lab<=8; lab++) (void)slk_set(lab,(char*)0,0);
}

/*AT&T
AT&T In order to use soft labels, this routine must be called before
AT&T initscr() or newterm() is called.  If initscr() winds up using a
AT&T line from stdscr to emulate the soft labels, then labfmt determines
AT&T how the labels are arranged on the screen.  Setting labfmt to 0
AT&T indicates that the labels are to be arranged in a 3-2-3 arrangement;
AT&T 1 asks for a 4-4 arrangement.
AT&T */

int
slk_init(int labfmt)
{
  if(labfmt!=0 && labfmt!=1) return(ERR);
  _slkfmt = labfmt;
  return(OK);
}
