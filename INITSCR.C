#include <stdlib.h>
#include "curses.h"
#include "screen.h"
#include "privfunc.h"

WINDOW *
initscr(void)
{
  (void)_newterm((char *)0, stdout, stdin, (int *)0);
  if(_screen == 0) return((WINDOW *)0);

  (void) clearok(curscr, TRUE);
#ifdef __STDC__
  atexit((void (*)(void))endwin);
#endif
  return(stdscr);
}
