#include "term.h"

#ifdef __STDC__
#define def(a,b,c) #c,
#else
#define def(a,b,c) "c",
#endif

char *numcodes[] = {
#include "numeric.cap"
(char *)0};
