#include "fmt.h"
#include "textcode.h"
#include "haveinline.h"

unsigned long fmt_quotedprintable(char* dest,const char* src,unsigned long len) {
  register const unsigned char* s=(const unsigned char*) src;
  unsigned long written=0,i;
  for (i=0; i<len; ++i) {
    if (s[i]&0x80 || s[i]=='=') {
      if (dest) {
	dest[written]='=';
	dest[written+1]=fmt_tohex(s[i]>>4);
	dest[written+2]=fmt_tohex(s[i]&15);
      }
      written+=3;
    } else {
      if (dest) dest[written]=s[i]; ++written;
    }
  }
  return written;
}
