#include "curses.h"
#include "term.h"
#include "screen.h"

#ifdef A_COLOR
/*AT&T
AT&T This routine changes the definition of a colour-pair.
AT&T It takes three arguments:  the number of the colour-pair to be
AT&T changed, the foreground colour number and the background colour number.
AT&T The value of the first argument must be between 1 and COLOR_PAIRS-1.
AT&T The value of the second and third arguments must be between 0 and
AT&T COLORS-1.  If the colour-pair was previously initialised, the screen
AT&T will be refreshed and all occurences of that colour-pair will be
AT&T changed to the new definition.  The routine returns OK if it was able
AT&T to change the definition of the colour-pair, ERR otherwise.
AT&T */

int
init_pair(int pair, short fg, short bg)
{
  PAIR *pptr;
  int update;

  if(cur_term->_colour_pairs == 0 ||
     (pair<1 || pair>COLOR_PAIRS) ||
     (fg<0 || fg>=COLORS) ||
     (bg<0 || bg>=COLORS))
    return(ERR);

  pptr = cur_term->_colour_pairs + pair;
  update = pptr->fg != DEFAULT_PAIR;
  pptr->fg = fg;
  pptr->bg = bg;
  return(update ? (clearok(curscr, TRUE) == ERR ? ERR : doupdate()) :OK);
}
#endif
