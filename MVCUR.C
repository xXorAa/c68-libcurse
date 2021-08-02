#include "curses.h"
#include "term.h"

/*AT&T
AT&T Low-level cursor motion.  If oldrow or oldcol are -1 then it means
AT&T that the position of the cursor is unknown and only strings which
AT&T will exactly determine the cursor position may be used.
AT&T */

int
mvcur(int oldrow, int oldcol, int newrow, int newcol)
{
  int i;

  if((oldrow == newrow) && (oldcol == newcol)) return(OK);

  if((newrow == 0) && (newcol == 0) && cursor_home)
    return(putp(cursor_home));

  if(newrow == oldrow)
    {
    if((newcol==0) && carriage_return) return(putp(carriage_return));
    if(oldcol != -1)
      {
      /* starting point known - can use relative motion */
      if(newcol > oldcol)
        {
	if(tab && (newcol % init_tabs == 0) && (newcol-oldcol)/init_tabs == 1) return(putp(tab));
        if((newcol == oldcol+1) && cursor_right) return(putp(cursor_right));
        if(parm_right_cursor) return(putp(tparm(parm_right_cursor,(long)(newcol-oldcol))));
        }
      else
        {
	if(back_tab && (newcol % init_tabs == 0) && (oldcol-newcol)/init_tabs == 1) return(putp(back_tab));
        if((newcol == oldcol-1) && cursor_left) return(putp(cursor_left));
        if(parm_left_cursor) return(putp(tparm(parm_left_cursor,(long)(oldcol-newcol))));
        }
      }
    if(column_address) return(putp(tparm(column_address,(long)newcol)));
    }

  if(newcol == oldcol)
    {
    if(oldrow != -1)
      {
      /* starting point known - can use relative motion */
      if(newrow > oldrow)
        {
        if((newrow == oldrow+1) && cursor_down) return(putp(cursor_down));
        if(parm_down_cursor) return(putp(tparm(parm_down_cursor,(long)(newrow-oldrow))));
        }
      else
        {
        if((newrow == oldrow-1) && cursor_up) return(putp(cursor_up));
        if(parm_up_cursor) return(putp(tparm(parm_up_cursor,(long)(oldrow-newrow))));
        }
      }
    if(row_address) return(putp(tparm(row_address,(long)newrow)));
    }

  if(cursor_address)
    return(putp(tparm(cursor_address,(long)newrow,(long)newcol)));

  /* Hmm... must try harder */
  if(newrow == oldrow)
    {
    if(oldcol != -1)
      {
      /* starting point known - can use relative motion */
      if(newcol > oldcol)
        {
        /* .. could use tab movement here .. */
        if(cursor_right)
          {
          for(i=newcol-oldcol; i>0; i--) (void)putp(cursor_right);
          return(OK);
          }
        }
      else
        {
        /* .. could use backtab movement here .. */
        if(cursor_left)
          {
          for(i=oldcol-newcol; i>0; i--) (void)putp(cursor_left);
          return(OK);
          }
        }
      }
    }

  if(newcol == oldcol)
    {
    if(oldrow != -1)
      {
      /* starting point known - can use relative motion */
      if(newrow > oldrow)
        {
        if(cursor_down)
          {
          for(i=newrow-oldrow; i>0; i--) (void)putp(cursor_down);
          return(OK);
          }
        }
      else
        {
        if(cursor_up)
          {
          for(i=oldrow-newrow; i>0; i--) (void)putp(cursor_up);
          return(OK);
          }
        }
      }
    }

  /* Still no success?  Try even harder */

  if(oldrow == -1)
    {
    if(cursor_home && (parm_down_cursor || cursor_down) && (parm_right_cursor || cursor_right))
      {
      (void)putp(cursor_home);
      return(mvcur(0,0,newrow,newcol));
      }
    }
  else if(oldcol == -1)
    {
    if(carriage_return && (parm_right_cursor || cursor_right))
      {
      (void)putp(carriage_return);
      return(mvcur(oldcol,0,newrow,newcol));
      }
    }

  /* Sorry, just cannot do the movement requested */
  return(ERR);
}

