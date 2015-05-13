#define _GNU_SOURCE
#define __deprecated__
#include "scan.h"
#include "byte.h"
#include "case.h"
#include <time.h>
#include <stdlib.h>

#ifdef sgi
extern char** environ;
#endif

/* "2014-05-27T19:22:16Z" */
size_t scan_iso8601(const char* in,struct timespec* t) {
  struct tm x;
  const char* c;
  unsigned long tmp;
  if (!(c=in)) return 0;
  if (scan_ulong(c,&tmp)!=4 || c[4]!='-') return 0; c+=5; x.tm_year=(int)(tmp-1900);
  if (scan_ulong(c,&tmp)!=2 || c[2]!='-') return 0; c+=3; x.tm_mon=(int)(tmp-1);
  if (scan_ulong(c,&tmp)!=2 || c[2]!='T') return 0; c+=3; x.tm_mday=(int)tmp;
  if (scan_ulong(c,&tmp)!=2 || c[2]!=':') return 0; c+=3; x.tm_hour=(int)tmp;
  if (scan_ulong(c,&tmp)!=2 || c[2]!=':') return 0; c+=3; x.tm_min=(int)tmp;
  if (scan_ulong(c,&tmp)!=2) return 0; c+=2; x.tm_sec=(int)tmp;
  if (*c=='.') {
    size_t i;
    ++c;
    i=scan_ulong(c,&tmp);
    c+=i;
    if (i<1 || i>9)
      t->tv_nsec=0;
    else {
      while (i<9) {
	++i;
	tmp*=10;
      }
      t->tv_nsec=tmp;
    }
  }

  x.tm_wday=x.tm_yday=x.tm_isdst=0;
#if defined(__dietlibc__) || defined(__GLIBC__)
  t->tv_sec=timegm(&x);
#elif defined(__MINGW32__)
  t->tv_sec=mktime(&x);
#else
  {
#ifdef sgi
    char** old=environ;
    char** newenv={0};
    environ=newenv;
    t->tv_sec=mktime(&x);
    environ=old;
#else
    char* old=getenv("TZ");
    unsetenv("TZ");
    t->tv_sec=mktime(&x);
    if (old) setenv("TZ",old,1);
#endif
  }
#endif

  if (*c=='+' || *c=='-') {
    int signum = (*c=='+') - (*c=='-');
    unsigned int val;
    ++c;
    if (scan_ulong(c,&tmp)!=2 || c[2]!=':') return 0; c+=3; val=tmp*60;
    if (scan_ulong(c,&tmp)!=2) return 0; c+=2; val+=tmp;
    t->tv_sec+=signum*val;
  } else if (*c=='Z')
    ++c;
  else
    return 0;
  return (size_t)(c-in);
}
