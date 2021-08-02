#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include "term.h"

#define RPN_STACK  30    /* size of the RPN stack */
#define push(v)    (*top_of_stack++ = v)
#define pop()      (*(--top_of_stack))
#define if_push(v) (*(++top_of_if_stack) = v)
#define if_pop()   (*(top_of_if_stack--))
#define outch(b,c) if(*top_of_if_stack) *(b)++ = c


/*AT&T
AT&T Instantiate the string str with params p.  A pointer is returned
AT&T to the result of str with the parameters applied.
AT&T
AT&T The parameter machanism uses a stack and special % codes to
AT&T manipulate it in the manner of a Reverse Polish Notation (postfix)
AT&T calculator.  Typically a sequence will push one of the parameters
AT&T onto the stack and then print it in some format.  Often more complex
AT&T operations are nexessary.  Binary operations are in postfix form with
AT&T the operands in the usual order.
AT&T
AT&T %%    output '%'
AT&T %[[:]flags][width][.precision][doxXs] like a printf
AT&T %c    print pop()
AT&T
AT&T %p[1-9]  push ith parameter
AT&T %P[a-z]  set variable [a-z] to pop()
AT&T %g[a-z]  get variable [a-z] and push it
AT&T %'c'     push char constant 'c'
AT&T %{nn}    push decimal constant nn
AT&T %l       push strlen (pop())
AT&T
AT&T %+    plus
AT&T %-    minus
AT&T %*    multiply
AT&T %/    divide
AT&T %m    modulus
AT&T %&    and
AT&T %|    or
AT&T %^    exclusive or
AT&T %=    equals
AT&T %>    greater then
AT&T %<    less than
AT&T %A    logical and
AT&T %O    logical or
AT&T %!    not
AT&T %~    negate
AT&T %i    (ANSI) add 1 to first two parameters
AT&T
AT&T %? expr %t then-part [ %e else-part ] %;  if statement
AT&T */

char *
tparm(char *str, ...)
{
  static long stack[RPN_STACK];
  static char if_stack[RPN_STACK];
  static char buffer[BUFSIZ];
  static int  variable[52];
  long *top_of_stack;
  char *top_of_if_stack;
  char buf[128];
  char *b;
  char *sptr;
  int  *iptr, *eptr;
  int  ansi = 0;
  int  ch;
  va_list ap;
  long  p[9];
  int lastp = 0;
#define p1 p[0]
#define p2 p[1]
#define p3 p[2]
#define p4 p[3]
#define p5 p[4]
#define p6 p[5]
#define p7 p[6]
#define p8 p[7]
#define p9 p[8]
  va_start(ap,str);

  if(str == 0) return((char *)0);

  top_of_stack = stack;
  top_of_if_stack = if_stack - 1;
  if_push(1) ;  /* so that normally we will output */

  /* clear out the variables 'a' to 'z' */
  for(iptr=variable, eptr=variable+26; iptr != eptr; iptr++) *iptr = 0;
    
  for(sptr=buffer; *str; )
    {
    if((ch = *str++) == '%')
      {
      switch(ch = *str++)
        {
      case '%':
        /* output a % */
        outch(sptr, ch);
        break;
      case 'd':
        /* print decimal number */
        (void)sprintf((b = buf), "%d", (int)pop());
        for(; *b; b++) outch(sptr, *b);
        break;
      case 'p':
        /* push parameter onto stack */
        {
        int pn = *str - '0';
        if(pn>=1 && pn<=9) while(lastp<pn) p[lastp++] = va_arg(ap,long);
        }
        switch(*str++)
          {
        case '1': push(p1+ansi); break;
        case '2': push(p2+ansi); break;
        case '3': push(p3); break;
        case '4': push(p4); break;
        case '5': push(p5); break;
        case '6': push(p6); break;
        case '7': push(p7); break;
        case '8': push(p8); break;
        case '9': push(p9); break;
          }
        break;
      case 'P':
        /* set variable from the stack */
        ch = *str++;
        if(islower(ch)) variable[ch-'a'] = (int)pop();
        else if(isupper(ch)) variable[ch-'A'+26] = (int)pop();
        break;
      case 'g':
        /* push variable onto stack */
        ch = *str++ ;
        if(islower(ch)) push(variable[ch-'a']);
        else if(isupper(ch)) push(variable[ch-'A'+26]);
        break;
      case '\'':
        push(*str++);
        str++;
        break;
      case '{':
        for(ch=0; isdigit(*str); str++) ch = ch*10 + (*str - '0');
        push(ch);
        str++;
        break;
      case 'l':
        push(strlen((char *)pop()));
        break;
      case 'c':
        /* output top of stack as a character */
        ch = (char)pop();
        *sptr++ = (ch==0)?0x80:ch;
        break;

      case '+': push(pop() + pop()); break;
      case '-': push(pop() - pop()); break;
      case '*': push(pop() * pop()); break;
      case '/': push(pop() / pop()); break;
      case 'm': push(pop() % pop()); break;
      case '&': push(pop() & pop()); break;
      case '|': push(pop() | pop()); break;
      case '^': push(pop() ^ pop()); break;
      case '=': push(pop() == pop()); break;
      case '>': push(pop() > pop()); break;
      case '<': push(pop() < pop()); break;
      case 'A': push(pop() && pop()); break;
      case 'O': push(pop() || pop()); break;
      case '!': push(!pop()); break;
      case '~': push(~pop()); break;
      case 'i': ansi = 1; break;
      case '?': if_push(1); break;
      case 't': ch = if_pop(); if_push(pop()!=0); break;
      case 'e': if_push(!if_pop()); break;
      case ';': ch = if_pop(); break;
      default: outch(sptr, ch); break;
        }
      }
    else
      outch(sptr, ch);
    }
  *sptr = '\0';
  va_end(ap);
  return(buffer);
}
