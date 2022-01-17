#include "curses.h"
#include "term.h"

#ifdef A_COLOR
/*AT&T
AT&T This routine gives users a way to find the intensity of the red,
AT&T green, and blue (RGB) components in a colour.
AT&T It requires four arguments:  the colour number, and three
AT&T addresses of shorts for storing the information about the
AT&T amounts of red, green, and blue components in the given colour.
AT&T The value of the first argument must be between 0 and COLORS-1.
AT&T The values that will be stored at the addresses pointed to by the
AT&T last three arguments will be between 0 (no component) and 1000
AT&T (maximum amount of component).
AT&T This routine returns ERR if the colour does not exist (the first
AT&T argument is outside the valid range), or if the terminal cannot
AT&T change colour definition, OK otherwise.
AT&T */

int
color_content(int colour, short *rptr, short *gptr, short *bptr)
{
  CONTENT *cptr;

  if(rptr == 0 || gptr == 0 || bptr == 0 || (colour<0 || colour>=COLORS))
    return(ERR);

  cptr = cur_term->_colour_content + colour;
  *rptr = cptr->red;
  *gptr = cptr->green;
  *bptr = cptr->blue;
  return(OK);
}
#endif
