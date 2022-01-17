#include <stdlib.h>
#include "curses.h"
#include "term.h"
#include "screen.h"
#include "privfunc.h"

static void adjustkeynode(_KEYNODE *key, _KEYNODE *old, _KEYNODE *new)
{
  if(key->right!=0)
    {
    adjustkeynode(key->right,old,new);
    key->right = new + (key->right - old);
    }
  if(key->left!=0)
    {
    adjustkeynode(key->left,old,new);
    key->left = new + (key->left - old);
    }
}

static _KEYNODE *newkeynode(_KEYNODE *keys, int number)
{
  _KEYNODE *kn = keys == NULL ?
    (_KEYNODE *) malloc (sizeof(_KEYNODE)*number) :
    (_KEYNODE *) realloc((void *)keys,sizeof(_KEYNODE)*number);
  if(keys != 0 && keys != kn) adjustkeynode(kn,keys,kn);
  return(kn);
}

/*
     This routine builts up the binary tree which is used to map a
     character string to a function key.  A function key in this
     context is any key which is not an ASCII type key,
     eg. the arrow keys, home key etc.
    
     This routine relies on the key entries in the TERMINAL
     structure being consequtive and in their numeric order.
*/

_KEYNODE *
_newkeys(void)
{
  int maxnodes = 200, nodes = 0;
  _KEYNODE *kptr, **pkptr, *khead = newkeynode((_KEYNODE*)0,maxnodes);
  char **sptr, **eptr = &key_mouse + 1;
  char *str;
  int val = KEY_MIN;

  for(sptr = &key_break; sptr != eptr; sptr++, val++)
    {
    if(*sptr == (char*)0) continue;

    pkptr = (_KEYNODE**)0;
    kptr = (nodes==0)?(_KEYNODE*)0:khead;
    for(str = *sptr; *str; str++)
      {
      while(kptr && *str)
        {
        if(*str == kptr->ch)
          {
          kptr = *(pkptr=&kptr->right);
          str++;
          }
        else
          kptr = *(pkptr=&kptr->left);
        }
      if(*str==0)
        {
        /* non unique key sequence !! */
        (void)fprintf(stderr,"Key sequence for %s not unique\n",
                strfnames[sptr - (&cur_term->_string_starter + 1)]);
        exit(1);
        }
      if(nodes==maxnodes) khead = newkeynode(khead,maxnodes+=20);
      kptr = &khead[nodes++];
      kptr->left = kptr->right = (_KEYNODE*)0;
      kptr->ch   = *str;
      kptr->val  = *(str+1) ? 0 : val;
      if(pkptr!=(_KEYNODE**)0) *pkptr = kptr;
      pkptr = &kptr->right;
      kptr = (_KEYNODE*)0;
      }
    }
  if(nodes==0) return((_KEYNODE*)0);
  return(newkeynode(khead,nodes));
}
