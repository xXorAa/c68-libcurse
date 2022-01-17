#include <unistd.h>
#include <termios.h>
#include "term.h"

/*AT&T
AT&T Returns the output speed of the terminal.  The number returned
AT&T is in  bits per second, for example 9600, and is an integer.
AT&T */

int
baudrate(void)
{
  struct termios t;

  if(cur_term == 0) return(0);
  if(tcgetattr(cur_term->_outfd, &t) == -1) return(0);
  switch(cfgetispeed(&t))
  {
    case B0:     return(0);
    case B50:    return(50);
    case B75:    return(75);
    case B110:   return(110);
    case B134:   return(134);
    case B150:   return(150);
    case B200:   return(200);
    case B300:   return(300);
    case B600:   return(600);
    case B1200:  return(1200);
    case B1800:  return(1800);
    case B2400:  return(2400);
    case B4800:  return(4800);
    case B9600:  return(9600);
    case B19200: return(19200);
    case B38400: return(38400);
  }
  return (0);
}
