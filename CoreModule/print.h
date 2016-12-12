#ifndef PRINT_H
#define PRINT_H

#include "stdarg.h"
#include "stdio.h"
#include <GL/glew.h>
#include <GL/glut.h>

class print {
    public:
        static void printString(const char* format, ...);
    private:
        static void printv(va_list args, const char* format);
        static void printAt(int x, int y, const char* format, ...);
        static void errCheck(char* where);
};

#endif // PRINT_H
