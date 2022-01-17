#include "curses.h"
#include "screen.h"
#include "privfunc.h"

/*
This routine is an internal routine which pushes the character
back onto the input stream.
*/
void
_ungetchar(int ch)
{
  _screen->_chars[_screen->_chars_read++] = ch;
}
