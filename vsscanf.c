#include <string.h>
#include "curses.h"
#include "privfunc.h"

int
_vsscanf(char *buf, char *fmt, va_list args)
{
#ifdef ARCH
  FILE f;
  int cnt;
  f.i_ptr = f.i_base = (unsigned char *)buf;
  f.i_cnt = f.bufsiz = strlen(buf);
  f.flag = _IOREAD | _IOFBF | _IOEOF;
  f.pos = 0;
  f.fd = -1;
  __scanf(&f,fmt,args,&cnt);
  return(cnt);
#else
  extern int __vsscanf(char *, char *, ...);	/* internal routine to estdio */
  return (__vsscanf(buf,fmt,args));
#endif
}
