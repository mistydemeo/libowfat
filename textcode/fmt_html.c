#include "fmt.h"
#include "textcode.h"
#include "str.h"
#include "haveinline.h"

unsigned int fmt_html(char* dest,const char* src,unsigned int len) {
  register const unsigned char* s=(const unsigned char*) src;
  unsigned long written=0,i;
  const char* seq;
  for (i=0; i<len; ++i) {
    switch (s[i]) {
    case '&': seq="&amp;"; goto doit;
    case '<': seq="&lt;"; goto doit;
    case '>': seq="&gt;"; goto doit;
    case '\n':
	seq="<br>";
      doit:
	written+=fmt_str(dest?dest+written:0,"&gt;");
	break;
    default: if (dest) dest[written]=s[i]; ++written; break;
    }
  }
  return written;
}
