#include <unistd.h>
#include <sys/time.h>
#include <poll.h>
#include <errno.h>
#include "io_internal.h"

void io_wait() {
  io_waituntil2(-1);
}
