#include <ctype.h>
#include "curses.h"
#include "window.h"

/*AT&T
AT&T The character ch is put into the window at the current cursor
AT&T position of the window and the position of the window cursor
AT&T is advanced.  Its function is similar to that of putchar().
AT&T At the right margin, an automatic newline is performed.
AT&T At the bottom of the scrolling region, if scrollok() is enabled,
AT&T the scrolling region will be scrolled up one line.
AT&T
AT&T If ch is a tab, newline, or backspace, the cursor will be moved
AT&T appropriately within the window.  A newline also does a wclrtoeol()
AT&T before moving.  Tabs are concidered to be at every eigth column.
AT&T If ch is another control character, it will be drawn in the ^X notation.
AT&T (Calling winch() on a position in the window containing a control
AT&T character will not return the control character, but instead will
AT&T return one character of the representation of the control character.)
AT&T
AT&T Video attributes can be combined with a character by OR-ing them
AT&T into the parameter.  This will result in these attributes also
AT&T being set.  (The intent here is that text, including attributes,
AT&T can be copied from one place to another using winch() and waddch().)
AT&T
AT&T Note the ch is actually of type chtype, not a character.
AT&T */

int
waddch(WINDOW *win, chtype ch)
{
  _LINE *yptr;
  int cury, curx;
  int c;

  if(win == 0) return(ERR);

  curx = win->_curx;
  cury = win->_cury;

  switch(c = (int) (ch & A_CHARTEXT))
    {
  case '\t' :
      {
      ch = 0;
      for(; ((curx+1)%8)!=0; curx++) {}
      break;
      }
  case '\r' :
      {
      ch = 0;
      curx = -1; 
      break;
      }
  case '\n' :
      {
      ch = 0;
      (void) wclrtoeol(win);
      curx = win->_cols;
      break;
      }
  case '\b' :
      {
      ch = 0;
      curx -= 2;
      break;
      }
  case ' ' :
      {
      ch = (win->_attr & A_CHARTEXT) | (ch & A_ATTRIBUTES);
      break;
      }
  default :
      {
      if(iscntrl(c))
        {
        char *s;
        ch &= A_ATTRIBUTES;
        for(s=unctrl(c); *s; s++) (void)waddch(win, *s | ch);
        return(OK);
        }
      }
    }

  yptr = win->_lines + cury;

  if(ch!=0)
    {
    yptr->line[curx] = ch | (win->_attr & A_ATTRIBUTES);
    if(curx < yptr->first) yptr->first = curx;
    if(curx > yptr->last) yptr->last = curx;
    win->_flags |= F_DIRTY;
    }

  win->_cury = cury;
  win->_curx = curx + 1;
  if(win->_curx >= win->_cols)
    {
    win->_curx = 0;
    win->_cury++;
    if(win->_cury > win->_bot)
      {
      if(win->_flags & F_SCROLL)
        {
        (void)wscrl(win,1);
        (void)wrefresh(win);
        }
      win->_cury--;
      }
    }

  return(win->_flags & F_IMMED ? wrefresh(win) : OK);
}
