#include <stdlib.h>
#include "curses.h"
#include "term.h"
#include "screen.h"

#ifdef A_COLOR
/*AT&T
AT&T This routine requires no arguments.  It must be called if the
AT&T user wants to use colours, and before any other colour manipulation
AT&T routine is called.  It is good practice to call this routine right
AT&T after initscr().
AT&T start_color() initialises eight basic colours (black, blue, green,
AT&T cyan, red, magenta, yellow, and white), and two global variables,
AT&T COLORS and COLOR_PAIRS (respectively defining the maximum number
AT&T of colours and colour-pairs the terminal can support).  It also
AT&T restores the terminal's colours to the values they had when the
AT&T terminal was just turned on.  It returns ERR if the terminal does
AT&T not support colours, OK otherwise.
AT&T */

int
start_color(void)
{
  PAIR *sptr, *eptr;
  CONTENT *bptr, *tptr;
  int colour;

  if(((COLOR_PAIRS = max_pairs) < 1)) return(ERR);
  COLORS = max_colors;

  cur_term->_colour_pairs = (PAIR *)malloc(sizeof(PAIR)*(COLOR_PAIRS+1));
  if(cur_term->_colour_pairs != 0)
    {
    for(sptr = cur_term->_colour_pairs,
        eptr = sptr + COLOR_PAIRS + 1;
        sptr != eptr;
        sptr++)
      {
      sptr->fg = sptr->bg = DEFAULT_PAIR;
      }
    cur_term->_colour_content = (CONTENT *)malloc(sizeof(CONTENT)*COLORS);
    if(cur_term->_colour_content != 0)
      {
      for(colour = 0, 
          tptr = cur_term->_colour_content,
          bptr = tptr + COLORS;
          bptr != tptr;
          tptr++, colour++)
        {
        tptr->red = (colour%1) * 1000;
        tptr->green = ((colour%2)>>1) * 1000;
        tptr->blue = ((colour%4)>>2) * 1000;
        }
      return(OK);
      }
    free((void *)cur_term->_colour_pairs);
    }
  COLORS = COLOR_PAIRS = 0;
  return(ERR);

}
#endif
