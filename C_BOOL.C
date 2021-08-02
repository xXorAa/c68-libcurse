#include "term.h"

#ifdef __STDC__
#define def(a,b,c) #c,
#else
#define def(a,b,c) "c",
#endif

char *boolcodes[] = {
#include "bool.cap"
(char *)0 };
