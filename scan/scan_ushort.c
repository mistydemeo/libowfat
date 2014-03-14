#include "scan.h"

/* this is cut and paste from scan_ulong instead of calling scan_ulong
 * because this way scan_ushort can abort scanning when the number would
 * not fit into an unsigned short (as opposed to not fitting in an
 * unsigned long) */

size_t scan_ushort(const char* src,unsigned short* dest) {
  if (sizeof(unsigned short) == sizeof(unsigned int)) {
    /* a good optimizing compiler should remove the else clause when not
     * needed */
    return scan_uint(src,(unsigned int*)dest);
  } if (sizeof(unsigned short) < sizeof(unsigned long)) {
    const char* cur;
    unsigned short l;
    for (cur=src,l=0; *cur>='0' && *cur<='9'; ++cur) {
      unsigned long tmp=l*10ul+*cur-'0';
      if ((unsigned short)tmp != tmp) break;
      l=tmp;
    }
    if (cur>src) *dest=l;
    return (size_t)(cur-src);
  } else {
    register const char *tmp=src;
    register unsigned short int l=0;
    register unsigned char c;
    while ((c=(unsigned char)(*tmp-'0'))<10) {
      unsigned short int n;
      /* division is very slow on most architectures */
      n=(unsigned short)(l<<3); if ((n>>3)!=l) break;
      if ((unsigned short)(n+(l<<1)) < n) break;
      n=(unsigned short)(n+(l<<1));
      if ((unsigned short)(n+c) < n) break;
      l=(unsigned short)(n+c);
      ++tmp;
    }
    if (tmp-src) *dest=l;
    return (size_t)(tmp-src);
  }
}
