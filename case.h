#ifndef CASE_H
#define CASE_H

/* turn upper case letters to lower case letters, ASCIIZ */
void case_lowers(char *s);
/* turn upper case letters to lower case letters, binary */
void case_lowerb(void *buf,unsigned long len);

/* like str_diff, ignoring case */
int case_diffs(const char *,const char *);
/* like byte_diff, ignoring case */
int case_diffb(const void *,unsigned long,const void *);

/* like str_start, ignoring case */
int case_starts(const char *,const char *);

#define case_equals(s,t) (!case_diffs((s),(t)))
#define case_equalb(s,n,t) (!case_diffb((s),(n),(t)))

#endif
