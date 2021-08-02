#include <string.h>
#include <stdlib.h>
#include "curses.h"
#include "term.h"
#include "config.h"

/*AT&T
AT&T Reads in the terminfo database, initialising the terminfo structures,
AT&T but does not set up the output virtualization structures used by curses.
AT&T The terminal type is in the character string term;  if term is NULL,
AT&T the environment variable TERM will be used.  All output is to the file
AT&T descriptor fildes,  If errret is not NULL, then setupterm() will return
AT&T OK or ERR and store a status value in the integer pointed to be errret.
AT&T A status of 1 in errret is normal, 0 means that the terminal could not
AT&T be found, and -1 means that the terminfo database could not be found.
AT&T If errret is NULL, setupterm() will print an error message upon finding
AT&T an error and exit.  Thus, the simplest call is
AT&T setupterm ((char *)0, 1, (int *)0), which uses all the defaults.
AT&T
AT&T The terminfo boolean, numeric and string variables are stored in a
AT&T structure of type TERMINAL.  After setupterm() returns successfully,
AT&T the variable cur_term (of type TERMINAL *), is initialised with all
AT&T of the information that the terminfo boolean, numeric and string
AT&T variables refer to.  The pointer may be saved before calling
AT&T setupterm() again.
AT&T Further calls to setupterm() will allocate new space rather than
AT&T reuse the space pointed to be cur_term.
AT&T */

static FILE *fd;
static TERMINAL *nterm;

#define MAGIC 0432

static void read_names(int namesize)
{
  /* read terminal names */
  nterm->_termdesc = (char *)malloc((size_t)namesize);
  (void)fread((void *)nterm->_termdesc, (size_t)namesize, (size_t)1, fd);
}

static void read_booleans(int boolsize)
{
  /* read booleans */
  char *sbptr = &nterm->_bool_starter + 1;
  char *ebptr = &nterm->_bool_terminator;

  for(; sbptr != ebptr && boolsize; sbptr++, boolsize--)
    {
    *sbptr = fgetc(fd);
    }
  for(; sbptr != ebptr; sbptr++) *sbptr = 0;
}

static void read_numerics(int numsize)
{
  /* read numerics */
  short *snptr = &nterm->_numeric_starter + 1;
  short *enptr = &nterm->_numeric_terminator;

  for(; snptr != enptr && numsize; snptr++, numsize--)
    {
    *snptr = fgetc(fd);
    *snptr += (fgetc(fd) <<8);
    }
  for(; snptr != enptr; snptr++) *snptr = -1;
}

static void read_strings(int strsize, int tabsize)
{
  /* read strings */
  unsigned int offset;
  char *table = (char *)malloc((size_t)tabsize);
  char **ssptr = &nterm->_string_starter + 1;
  char **esptr = &nterm->_string_terminator;

  /* use _string_starter to hold pointer to string table */
  nterm->_string_terminator = table;
  for(; strsize>0 && ssptr != esptr; ssptr++, strsize--)
    {
    offset = fgetc(fd);
    offset += (fgetc(fd) << 8);
#ifdef GENERIC
    *ssptr = (offset >= 0x8000U) ? (char *)0 : (table + offset);
#else
    *ssptr = (offset >= 0x8000) ? (char *)0 : (table + offset);
#endif
    }
  for(; ssptr != esptr; ssptr++) *ssptr = (char *)0;

  /* and finally the string table */
  (void)fread((void *)table, (size_t)tabsize, (size_t)1, fd);
}

int
setupterm(char *term, int fildes, int *errret)
{
  char  termnam[256];
  char  *terminfo;
  int   magic;
  int   namesize, boolsize, numsize, strsize, tabsize;

/*IMB*/fildes = fildes;
  if(errret) *errret = 1;

  if(term == 0 && getenv("TERM") == 0)
    {
    if(errret) return(*errret = 0, ERR);
    (void)fprintf(stderr,"no terminal defined\n");
    exit(1);
    }

  if((terminfo=getenv("TERMINFO")) == 0)
    terminfo = TERMDIR;

  if(term == 0) term = getenv("TERM");
  (void)strcat(strcat(strcpy(termnam, terminfo), DIR_SEPERATOR), term);

  if((fd=fopen(termnam,"r")) == 0)
    {
    if(errret) return(*errret = -1, ERR);
    (void)fprintf (stderr,"cannot open terminfo file '%s'\n",termnam);
    exit(1);
    }

  /* check that it is a valid terminfo file */
  magic = fgetc(fd);
  magic += (fgetc(fd) << 8);
  if(magic != MAGIC)
    {
    (void)fclose(fd);
    if(errret) return(*errret = 0, ERR);
    (void)fprintf(stderr,"bad magic on terminfo file '%s'\n",termnam);
    exit(1);
    }

  nterm = (TERMINAL *)calloc((size_t)1,sizeof(TERMINAL));
/*IMB check if malloc worked !!*/

  /* now read in the terminfo database */

  namesize = fgetc(fd) ;
  namesize += (fgetc(fd) <<8);

  boolsize = fgetc(fd);
  boolsize += (fgetc (fd) <<8);

  numsize = fgetc(fd);
  numsize += (fgetc(fd) <<8);

  strsize = fgetc(fd);
  strsize += (fgetc(fd) <<8);

  tabsize = fgetc(fd);
  tabsize += (fgetc(fd) <<8);

  read_names(namesize);

  read_booleans(boolsize);

  read_numerics(numsize);

  read_strings(strsize,tabsize);

  (void)fclose(fd);

  (void)set_curterm(nterm);

  cur_term->_supported_attr = termattrs();
  return(OK);
}
