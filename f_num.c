#include "term.h"

#ifdef __STDC__
#define def(a,b,c) #a,
#else
#define def(a,b,c) "a",
#endif

char *numfnames [] = {
#include "numeric.cap"
(char *)0};
