#ifndef BUFFER_H
#define BUFFER_H

typedef struct buffer {
  char *x;
  unsigned int p;
  unsigned int n;
  int fd;
  int (*op)();
} buffer;

#define BUFFER_INIT(op,fd,buf,len) { (buf), 0, (len), (fd), (op) }
#define BUFFER_INSIZE 8192
#define BUFFER_OUTSIZE 8192

extern void buffer_init(buffer* b,int (*op)(),int fd,char* y,unsigned int ylen);

extern int buffer_flush(buffer* b);
extern int buffer_put(buffer* b,const char* x,unsigned int len);
extern int buffer_putalign(buffer* b,const char* x,unsigned int len);
extern int buffer_putflush(buffer* b,const char* x,unsigned int len);
extern int buffer_puts(buffer* b,const char* x);
extern int buffer_putsalign(buffer* b,const char* x);
extern int buffer_putsflush(buffer* b,const char* x);

#define buffer_PUTC(s,c) \
  ( ((s)->n != (s)->p) \
    ? ( (s)->x[(s)->p++] = (c), 0 ) \
    : buffer_put((s),&(c),1) \
  )

extern int buffer_get(buffer* b,char* x,unsigned int len);
extern int buffer_bget(buffer* b,char* x,unsigned int len);
extern int buffer_feed(buffer* b);

extern char *buffer_peek(buffer* b);
extern void buffer_seek(buffer* b,unsigned int len);

#define buffer_PEEK(s) ( (s)->x + (s)->n )
#define buffer_SEEK(s,len) ( ( (s)->p -= (len) ) , ( (s)->n += (len) ) )

#define buffer_GETC(s,c) \
  ( ((s)->p > 0) \
    ? ( *(c) = (s)->x[(s)->n], buffer_SEEK((s),1), 1 ) \
    : buffer_get((s),(c),1) \
  )

extern int buffer_copy(buffer* out,buffer* in);

int buffer_putulong(buffer *b,unsigned long l);
int buffer_put8long(buffer *b,unsigned long l);
int buffer_putxlong(buffer *b,unsigned long l);
int buffer_putlong(buffer *b,unsigned long l);

extern buffer *buffer_0;
extern buffer *buffer_0small;
extern buffer *buffer_1;
extern buffer *buffer_1small;
extern buffer *buffer_2;

#endif
