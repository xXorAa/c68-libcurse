#include "curses.h"
#include "screen.h"

/*AT&T
AT&T The current contents of the virtual screen are written
AT&T to the file filename.
AT&T */

int
scr_dump(char *filename)
{
  FILE *fd;

  if(filename == 0 || _screen == 0) return(ERR);

  if((fd = fopen(filename, "w")) == NULL) return(ERR);
  (void)putwin(_screen->_physcr, fd);
  (void)fclose(fd);
  return(OK);
}
