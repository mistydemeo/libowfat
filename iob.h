#ifndef _IOB_H
#define _IOB_H

/* These functions can be used to create a queue of small (or large)
 * buffers and parts of files to be sent out over a socket.  It is meant
 * for writing HTTP servers or the like. */

/* This API works with non-blocking I/O.  Simply call iob_send until it
 * returns 0 (or -1).  The implementation uses sendfile for zero-copy
 * TCP and it will employ writev (or the built-in sendfile writev on
 * BSD) to make sure the output fragments are coalesced into as few TCP
 * frames as possible.  On Linux it will also use the TCP_CORK socket
 * option. */

#include "io.h"
#include "array.h"

typedef struct io_batch {
  array b;
  uint64 bytesleft;
  long next,bufs,files;
} io_batch;

io_batch* iob_new(int hint_entries);
int iob_addbuf(io_batch* b,const void* buf,uint64 n);
int iob_adds(io_batch* b,const char* s);
int iob_addfile(io_batch* b,int64 fd,uint64 off,uint64 n);
int64 iob_send(int64 s,io_batch* b);
void iob_reset(io_batch* b);

#endif
