#include <signal.h>
#include <unistd.h>
#include "curses.h"
#include "screen.h"
#include "window.h"
#include "privfunc.h"

static void dummy(int s) {s=s;}

/*
This routine is an internal routine which handles the mapping
of characters from the input stream to the function keys.
*/

int
_keymap(WINDOW *win, int ch)
{
  int ret;
  _KEYNODE *kptr;
  char *s;
  char str[INPUT_BUFFER_LEN+1];
  void (*sigsav)() = 0;
  int save_alarm = 0;

  for(s = str, ret = ch, kptr = _screen->_keys; kptr; )
    {
    if(kptr->ch != ch) {kptr = kptr->left; continue;}

    /* reset push-back buffer */
    if(kptr->val!=0) {s = str; ret = kptr->val;}
    if((kptr = kptr->right) == 0) break;

    if(win->_flags & F_TIMEOUT)
      {
      sigsav = signal(SIGALRM, dummy);
      save_alarm = alarm(1);
      }

    ch = _getchar();

    if(win->_flags & F_TIMEOUT)
      {
      (void)alarm(save_alarm);
      (void)signal(SIGALRM, sigsav);
      }

    if(ch < 0) break;
    *(++s) = ch;  /* save character in push-back buffer */
    }

  /* must now put any characters not matched onto the input stream */
  while(s != str) _ungetchar((int)*s--);
  return(ret);
}
