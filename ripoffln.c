#include "curses.h"
#include "screen.h"
#include "privfunc.h"

typedef int (*INITPROC)(WINDOW*,int);

#define MAXRIPOFFS 5

static int rip_count = 0;
static int rip_line[MAXRIPOFFS];
static INITPROC rip_init[MAXRIPOFFS];

void
_ripoff_init(void)
{
  int i;
  int topln = _screen->_stdtop;
  int botln = _screen->_stdbot;
  for(i=0; i<rip_count; i++)
    {
    int ln = rip_line[i];
    LINES--;
    (void)(*rip_init[i])(newwin(1, COLS, (ln<0)?(botln--):(topln++), 0), COLS);
    }
  _screen->_stdtop = topln;
  _screen->_stdbot = botln;
  rip_count = 0;
}

/*AT&T
AT&T This routine must be called before initscr() or newterm().
AT&T If line is positive, a line will be removed from the top of stdscr;
AT&T if negative, a line will be removed from the bottom.
AT&T When this is done inside initscr(), the routine init() is called
AT&T with two arguments:  a window pointer to the 1-line window that
AT&T has been allocated and an integer with the number of columns in
AT&T the window.
AT&T */

int
ripoffline(int line, INITPROC init)
{
  if(rip_count>=MAXRIPOFFS || init==0) return(ERR);
  rip_line[rip_count] = line;
  rip_init[rip_count++] = init;
  return(OK);
}
