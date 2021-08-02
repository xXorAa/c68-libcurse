#include "curses.h"
#include "term.h"

#ifdef A_COLOR
/*AT&T
AT&T This routine changes the definition of a colour.
AT&T It takes four arguments:  the number of the colour to be changed
AT&T followed by the three RGB values (for the amount of red, green,
AT&T and blue components).
AT&T The value of the first argument must be between 0 and COLORS-1.
AT&T The last three arguments must each be a value between 0 and 1000.
AT&T When init_color() is used, all occurrences of that colour on the
AT&T screen immediately change to the new definition.
AT&T It returns OK if it was able to change the definition of the colour,
AT&T ERR otherwise.
AT&T */

int
init_color(int colour, short red, short green, short blue)
{
  CONTENT *cptr;

  if((colour<0 || colour>=COLORS) ||
     (red<0 || red>1000) ||
     (green<0 || green>1000) ||
     (blue<0 || blue>1000))
    return(ERR);

  cptr = cur_term->_colour_content + colour;
  cptr->red = red;
  cptr->green = green;
  cptr->blue = blue;
  return(OK);
}
#endif
