#include <sys/types.h>
#include <unistd.h>
#ifdef __MINGW32__
#include <windows.h>
#else
#include <sys/mman.h>
#endif
#include "open.h"
#include "mmap.h"

extern char* mmap_shared(const char* filename,unsigned long* filesize) {
#ifdef __MINGW32__
  HANDLE fd,m;
  char* map;
  fd=CreateFile(filename,GENERIC_WRITE,FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
  if (fd==INVALID_HANDLE_VALUE)
    return 0;
  m=CreateFileMapping(fd,0,PAGE_READWRITE,0,0,NULL);
  map=0;
  if (m)
    map=MapViewOfFile(m,FILE_MAP_WRITE,0,0,0);
  CloseHandle(m);
  CloseHandle(fd);
  return map;
#else
  int fd=open_rw(filename);
  char *map;
  if (fd>=0) {
    *filesize=lseek(fd,0,SEEK_END);
    map=mmap(0,*filesize,PROT_WRITE,MAP_SHARED,fd,0);
    if (map==(char*)-1)
      map=0;
    close(fd);
    return map;
  }
  return 0;
#endif
}
