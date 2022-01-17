#include "term.h"

#ifdef __STDC__
#define def(a,b,c) #b,
#else
#define def(a,b,c) "b",
#endif

char *boolnames[] = {
#include "bool.cap"
(char *)0 };
