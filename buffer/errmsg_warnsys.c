#include <stdarg.h>
#include <sys/types.h>
#include "errmsg.h"
#include "str.h"
#include <string.h>
#include <errno.h>

extern void errmsg_writesys(int fd,const char* message,va_list list);

void errmsg_warnsys(const char* message, ...) {
  va_list a;
  va_start(a,message);
  errmsg_writesys(2,message,a);
  va_end(a);
}
