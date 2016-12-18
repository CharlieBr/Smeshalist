#include "print.h"

#define LEN 8192


void print::printv(va_list args, const char* format) {
  char buf[LEN];
  char* ch=buf;
  vsnprintf(buf,LEN,format,args);
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*ch++);
}

void print::printFont10(va_list args, const char* format) {
  char buf[LEN];
  char* ch=buf;
  vsnprintf(buf,LEN,format,args);
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*ch++);
}

void print::printStringFont10(const char* format, ...) {
  va_list args;
  va_start(args,format);
  printFont10(args,format);
  va_end(args);
}

void print::printString(const char* format, ...) {
  va_list args;
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

void print::printAt(int x, int y, const char* format, ...) {
  va_list args;
  glWindowPos2i(x,y);
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

void print::errCheck(char* where) {
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
