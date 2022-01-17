#include "curses.h"

extern int _overlay_overwrite (WINDOW*,WINDOW*,bool);

/*AT&T
AT&T This routine overlays text from srcwin on top of text
AT&T from dstwin wherever the two windows overlap.
AT&T */

int
overwrite(WINDOW *srcwin, WINDOW *dstwin)
{
  return(_overlay_overwrite(srcwin, dstwin, (bool)FALSE));
}
