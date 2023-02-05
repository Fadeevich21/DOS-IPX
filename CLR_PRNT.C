#include "prjct2\clr_prnt.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


void print_color(char* format, char* color, int n, ...) {
	char buf[512];
	va_list ap;

	buf[0] = '\0';
	va_start(ap, n);
	strcat(buf, color);
	strcat(buf, format);
	strcat(buf, COLOR_RESET);

	vprintf(buf, ap);

	va_end(ap);
}