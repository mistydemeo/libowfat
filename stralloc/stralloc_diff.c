#include "stralloc.h"
#include "byte.h"
#include "str.h"

extern int stralloc_diff(const stralloc* a,const stralloc* b) {
  register unsigned int i;
  register int j;
  for (i=0;;++i) {
    if (i==a->len) return i==b->len?0:-1; if (i==b->len) return 1;
    if ((j=(a->s[i]-b->s[i]))) return j;
  }
  return j;
}
