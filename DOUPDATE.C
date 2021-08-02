#include "curses.h"
#include "term.h"
#include "screen.h"
#include "window.h"
#include "privfunc.h"

static void clearthescreen(void)
{
  WINDOW *physcr = _screen->_physcr;
  register _LINE *ystart, *yend;
  int cols = physcr->_cols, rows = physcr->_rows;
  chtype ch;

  if(_screen->_state == SHELL_STATE)
    {
    if(exit_attribute_mode) (void)putp(tparm(exit_attribute_mode));

    (void)reset_prog_mode();
    if(enter_ca_mode != 0) (void)putp(enter_ca_mode);
    }

  if(clear_screen != 0) (void)putp(clear_screen);
  else if(cursor_home != 0 && clr_eos != 0)
    {
    (void)putp(cursor_home);
    (void)putp(clr_eos);
    }
  else
    {
    /* must clear the screen the hard way */
    int y, r = rows * 2;
    for(y = 0 ; y < r ; y++) putchar('\n');
    }
  physcr->_attr = A_NORMAL | ' ';
  physcr->_cury = physcr->_curx = -1;  /* cursor position is unknown */

  (void)touchwin(curscr);
  ch = physcr->_attr;
  ystart = physcr->_lines;
  yend = ystart + rows;
  for(; ystart != yend; ystart++)
    {
    register chtype *xstart = ystart->line;
    register chtype *xend = xstart + cols;
    for(; xstart != xend; xstart++) *xstart = ch;
    }
  _screen->_state = CURSES_STATE;
}

static void
domove(int oldy, int oldx, int y, int x)
{
  WINDOW *physcr = _screen->_physcr;

  if(!move_standout_mode && (physcr->_cury != y || (physcr->_curx-x>1)))
    {
    /* not safe to move in enhanced video mode */
    (void)vidattr (physcr->_attr & ~(A_STANDOUT|A_UNDERLINE));
    }
  if(physcr->_flags&F_INSERTED && (move_insert_mode == 0) && exit_insert_mode)
    {
    /* mustn't move in insert mode */
    (void)putp(exit_insert_mode);
    physcr->_flags &= ~F_INSERTED;
    }
  (void)mvcur(oldy, oldx, y, x);
}

static void
docharacter(chtype ch, int y, int x, bool ins)
{
  WINDOW *physcr = _screen->_physcr;

  domove(physcr->_cury, physcr->_curx, y, x);
  physcr->_cury = y;
  physcr->_curx = x;
  (void)vidattr(ch & A_ATTRIBUTES);
  if(ins)
    {
    if(physcr->_flags & F_INSERTED == 0 && enter_insert_mode) 
      {
      (void)putp(enter_insert_mode);
      physcr->_flags |= F_INSERTED;
      }
    if(insert_character) (void)putp(insert_character);
    }
  else
    if(physcr->_flags & F_INSERTED && exit_insert_mode)
      {
      (void)putp(exit_insert_mode);
      physcr->_flags &= ~F_INSERTED;
      }
  if(tilde_glitch && (ch & A_CHARTEXT == '~')) ch = ch & ~A_CHARTEXT | '-';
  putchar((int)(ch & A_CHARTEXT));
  if(eat_newline_glitch && x==physcr->_cols-1) physcr->_cury=physcr->_curx=-1;
}

/*AT&T
AT&T This routine compares the virtual screen to the physical screen
AT&T and does any updates necessary to make the two screens identical.
AT&T */

int
doupdate(void)
{
  WINDOW *physcr, *cscr;
  _LINE *ystart, *yend, *yptr;
  int y;
  bool am;

  if(_screen == 0) return(ERR);  /* screen never initialised */

  physcr = _screen->_physcr;
  cscr = curscr;

  if(cscr->_flags & F_CLEAR || _screen->_state != CURSES_STATE)
    {
    clearthescreen();
    }

  if(cscr->_flags & F_DIRTY)
    {
    /* check for scrolling of screen areas */
    _scroll_update();

    /* check for clearing of screen areas */
    _clr_update();

    /* changes not done by now must be written out individually */
    am = auto_right_margin;
    ystart = cscr->_lines;
    yend = ystart + cscr->_rows;
    yptr = physcr->_lines + cscr->_begy;
    for(y = 0; ystart != yend; ystart++, yptr++, y++)
      {
      chtype *xstart, *xend, *xptr;
      int x = ystart->first;
      if(x == FIRST_NOT_CHANGED) continue;
  
      xstart = ystart->line + x;
      xend = ystart->line + ystart->last + 1;
      xptr = yptr->line + x;
      for(; xstart != xend; xstart++, xptr++, x++)
        {
        if(*xptr == *xstart) continue;
  
        if((x == physcr->_cols-1) && (y == physcr->_rows-1))
          {
          /* last character on the screen */
          if(physcr->_flags & F_IC == 0) break;

          /* write the last character */
          docharacter(*xstart,y-1,x-1,TRUE);
          *xptr-- = *xstart--;

          /* re-write the 2nd to last character */
          (void)vidattr(*xstart & A_ATTRIBUTES);
          putchar((int)(*xstart & A_CHARTEXT));
          *xptr = *xstart;

          break;
          }

        docharacter(*xstart, y, x, FALSE);
        *xptr = *xstart;
  
        physcr->_curx++;
        if(physcr->_curx == physcr->_cols && am)
          {
          physcr->_curx = 0;
          physcr->_cury++;
          }
        }
      ystart->first = FIRST_NOT_CHANGED;
      ystart->last  = LAST_NOT_CHANGED;
      }
    }

  if(cscr->_flags & F_LEAVE)
    {
    domove(physcr->_cury, physcr->_curx, cscr->_cury, cscr->_curx);
    physcr->_cury = cscr->_cury;
    physcr->_curx = cscr->_curx;
    (void)curs_set(hard_cursor?2:1);
    }
  else
    (void)curs_set(0);

  if(cscr->_flags & F_KEYPAD != physcr->_flags & F_KEYPAD)
    {
    if(cscr->_flags & F_KEYPAD != 0)
      {
      if(keypad_xmit != 0) (void)putp(keypad_xmit);
      physcr->_flags |= F_KEYPAD;
      }
    else
      {
      if(keypad_local != 0) (void)putp(keypad_local);
      physcr->_flags &= ~F_KEYPAD;
      }
    }

  cscr->_flags &= F_KEYPAD;
  (void)fflush(_screen->_outfd);

  return(OK);
}
