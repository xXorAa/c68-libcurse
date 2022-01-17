#include "curses.h"

extern int _overlay_overwrite (WINDOW*,WINDOW*,bool);

/*AT&T
AT&T This routine overlays text from srcwin on top of text from dstwin
AT&T wherever the two windows overlap.  This routine is non-destructive
AT&T (blanks are not copied).
AT&T */

int
overlay(WINDOW *srcwin, WINDOW *dstwin)
{
  return(_overlay_overwrite(srcwin, dstwin, (bool)TRUE));
}
