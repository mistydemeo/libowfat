#include "fmt.h"

/* "foo" -> "foo  "
 * append padlen-srclen spaces after dest, if that is >= 0.  Truncate
 * only if total length is larger than maxlen.  Return number of
 * characters written. */
unsigned long fmt_fill(char* dest,unsigned long srclen,unsigned long padlen,unsigned long maxlen) {
  long todo;
  char* olddest=dest;
  char* max=dest+maxlen;
  if (dest==0) {
    int sum=srclen>padlen?srclen:padlen;
    return sum>maxlen?maxlen:sum;
  }
  dest+=srclen;
  for (todo=padlen-srclen; todo>0; --todo) {
    if (dest>max) break;
    *dest=' '; ++dest;
  }
  return dest-olddest;
}
