#include "curses.h"

/*AT&T
AT&T This routine is analogous to wrefresh() except that pads, instead
AT&T of windows, are involved.  The additional parameters are needed
AT&T to indicate what part of the pad and screen are involved.
AT&T pminrow and pmincol specify the upper left corner, in the pad,
AT&T of the rectangle to be displayed.
AT&T sminrow, smincol, smaxrow and smaxcol specify the edges, on the
AT&T screen, of the rectangle to be displayed.
AT&T The lower right corner in the pad of the rectangle to be displayed
AT&T is calculated from the screen coordinates, since the rectangles
AT&T must be the same size.
AT&T Both rectangles must be entirely contained within their respective
AT&T structures.  Negative values of pminrow, pmincol, sminrow and
AT&T smincol are treated as if they were zero.
AT&T */

int
prefresh(WINDOW *pad, int pminrow, int pmincol, int sminrow,
         int smincol, int smaxrow, int smaxcol)
{
  return(pnoutrefresh(pad, pminrow, pmincol, sminrow, smincol,
                      smaxrow, smaxcol) == ERR ? ERR : doupdate());
}
