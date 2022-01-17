#include "curses.h"
#include "screen.h"

/*AT&T
AT&T This routine returns a pointer to a static area contining a verbose
AT&T description of the current terminal.  The maximum length of a verbose
AT&T description is 128 characters.
AT&T It is defined only after the call to initscr() or newterm().
AT&T The area is overwritten by each call to newterm() and is not
AT&T restored by set_term(), so the value should be saved between calls
AT&T to newterm() if longname() is going to be used with multiple terminals.
AT&T */

char *
longname(void)
{
	return (_longname);
}
