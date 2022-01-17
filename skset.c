#include <string.h>
#include "curses.h"
#include "screen.h"

/*AT&T
AT&T labnum is the label number, from 1 to 8.
AT&T label is the string to be put on the label, up to 8 characters in
AT&T length.  A NULL string or a NULL pointer will put up a blank label.
AT&T labfmt is one of 0, 1 or 2, to indicate whether the label is to be
AT&T left-justified, centered, or right-justified within the label.
AT&T */

int
slk_set(int labnum, char *label, int labfmt)
{
  WINDOW *slkscr;
  int start;
  int len;

  if(_screen == 0
     || (slkscr = _screen->_slkscr) == 0
     || (labnum<0 || labnum>8)
     || (labfmt<0 || labfmt>2))
    return(ERR);

  start = (labnum-1) * 9 + ((_screen->_slkfmt==1) ?
          (labnum<4 ? 3 :(labnum < 6 ? 4 : 5)) :
          (labnum<5 ? 3 : 5));

  /* first of all clear the slk label */
  (void)mvwaddstr(slkscr,0,start,"        ");

  /* save it away */
  if(label == 0) _screen->_slk_labels[(labnum-1)*9] = '\0';
  else (void)strncpy(&_screen->_slk_labels[(labnum-1)*9], label, (size_t)8);

  if(label == 0 || *label == '\0') return(OK);

  /* work out justification */
  if((len = strlen(label)) < 8)
    {
    switch(labfmt)
      {
    case 0 : /* Left justified   */ break;
    case 1 : /* center justified */ start += (8-len)/2; break;
    case 2 : /* right justified  */ start += (8-len); break;
      }
    }
  else
    len = 8;

  /* and now write the new slk label */
  return(mvwaddnstr(slkscr,0,start,label,len));
}
