#include "buffer.h"

int buffer_putflush(buffer* b,const unsigned char* x,unsigned long int len) {
  if (buffer_put(b,x,len)<0) return -1;
  if (buffer_flush(b)<0) return -1;
  return 0;
}
