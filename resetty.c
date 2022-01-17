#include "curses.h"
#include "term.h"
#include "privfunc.h"

/*AT&T
AT&T The resetty() routine restores the state of the terminal modes
AT&T from a buffer.
AT&T */

int
resetty(void)
{
 return( tcsetattr(0, TCSADRAIN, &_tty_state) );
}
