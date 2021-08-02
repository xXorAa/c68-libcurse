#include <string.h>
#include "curses.h"
#include "term.h"

#define checkstr(sptr,pptr) (strstr(sptr,pptr)!=0)

/*AT&T
AT&T If a given terminal doesn't support a video attribute that an
AT&T application program is trying to use, curses may substitute a
AT&T different video attribute for it.  The termattrs function returns
AT&T a logical OR of all video attributes supported by the terminal.
AT&T This information is useful when a curses program needs complete
AT&T control over the appearance of the screen.
AT&T */

chtype
termattrs(void)
{
  chtype attr = A_NORMAL;

  if(set_attributes)
    {
    /* must look to see what parameters are used */
    if(checkstr(set_attributes, "%p1")) attr |= A_STANDOUT;
    if(checkstr(set_attributes, "%p2")) attr |= A_UNDERLINE;
    if(checkstr(set_attributes, "%p3")) attr |= A_REVERSE;
    if(checkstr(set_attributes, "%p4")) attr |= A_BLINK;
    if(checkstr(set_attributes, "%p5")) attr |= A_DIM;
    if(checkstr(set_attributes, "%p6")) attr |= A_BOLD;
    if(checkstr(set_attributes, "%p7")) attr |= A_INVIS;
    if(checkstr(set_attributes, "%p8")) attr |= A_PROTECT;
#ifdef A_ALTCHARSET
    if(checkstr(set_attributes, "%p9")) attr |= A_ALTCHARSET;
#endif
    }
  else
    {
    if(enter_standout_mode) attr |= A_STANDOUT;
    if(enter_underline_mode) attr |= A_UNDERLINE;
    if(enter_reverse_mode) attr |= A_REVERSE;
    if(enter_blink_mode) attr |= A_BLINK;
    if(enter_dim_mode) attr |= A_DIM;
    if(enter_bold_mode) attr |= A_BOLD;
    if(enter_protected_mode) attr |= A_PROTECT;
#ifdef A_ALTCHARSET
    if(enter_alt_charset_mode) attr |= A_ALTCHARSET;
#endif
    }

#ifdef A_COLOR
  /* if colour is being used then some attributes may be specified as
     not to be used with colour.              */

  if(cur_term->_colour_pairs && no_color_video > 0)
    attr &= ~(no_color_video + A_STANDOUT - 1);
#endif

  return(attr);
}
