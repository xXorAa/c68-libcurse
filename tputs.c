#include "curses.h"
#include "term.h"

/*AT&T
AT&T Apply padding to the string str and output it.
AT&T str must be a terminfo(4) string variable or the return value
AT&T from tparm(), tgetstr() or tgoto().
AT&T count is the number of lines affected, or 1 if not applicable.
AT&T putc is a putchar(3S)-like routine to which the characters are
AT&T passed, one at a time.
AT&T */

int
tputs(char *str, int count, int (*putch)(int))
{
  int c, delay, proportional, manditory, baud;
  char *s;
  if(str)
    {
    while((c=*str++) != 0)
      {
      switch (c)
        {
        case '$':
          if(*str=='<')
          {
            s = str+1;
            if (*s>='0' && *s<='9')
            {
              proportional = manditory = 0;
              for(delay=0; *s>='0' && *s<='9'; s++)
              {
                delay=delay*10+(*s-'0');
              }
              delay *= 10;
              if(*s == '.') s++;
              if(*s>='0' && *s<='9') delay+=(*s-'0');
              if(*s == '*') { proportional=1; s++; }
              if(*s == '/') { manditory=1; s++; }
              if(*s++ == '>')
                {
                /* this really is a padding specification */
                str = s;
                if(delay == 0 || (xon_xoff && !manditory)) continue;
                if((baud = baudrate()) < padding_baud_rate) continue;
                if(proportional) delay *= count;
                if(no_pad_char) (void)napms (delay/10);
                else
                  {
                  for ((delay = baud * delay / 10000) / 8; delay>0; delay--)
                    {
                      (void)(*putch)(pad_char?*pad_char:0);
                    }
                  }
                }
                break;
            }
          }
          (void)(*putch)(c);
          break;
        case 0x80:
          c = 0;
          /*FALLTHRU*/
        default:
          (void)(*putch)(c);
        }
      }
    }
  return(OK);
}
