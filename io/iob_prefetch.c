#include "iob_internal.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>

void iob_prefetch(io_batch* b,uint64 bytes) {
  volatile char x;
  iob_entry* e,* last;
  if (b->bytesleft==0) return;
  last=(iob_entry*)(((char*)array_start(&b->b))+array_bytes(&b->b));
  e=(iob_entry*)array_start(&b->b);
  if (!e) return;
  for (; e<last; ++e) {
    if (e->type==FROMFILE || e->type==FROMFILE_CLOSE) {
      char* c,* d;
      uint64 before=bytes;
      if (e->n<bytes) bytes=e->n;
      if (e->n>=1000000) {
	long l=e->offset&4095;
	d=c=mmap(0,bytes,PROT_READ,MAP_SHARED,e->fd,(e->offset|4095)+1);
	bytes-=l;
	if (c!=MAP_FAILED) {
	  while (bytes>4095) {
	    x=*d;
	    bytes-=4096;
	    d+=4096;
	  }
	}
	munmap(c,before);
      }
      return;
    }
  }
  (void)x;
}
