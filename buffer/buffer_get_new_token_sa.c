#include "stralloc.h"
#include "buffer.h"

int buffer_get_new_token_sa(buffer* b,stralloc* sa,const unsigned char* charset,unsigned long int setlen) {
  stralloc_zero(sa);
  return buffer_get_token_sa(b,sa,charset,setlen);
}
