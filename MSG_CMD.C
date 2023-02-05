#include "prjct2\msg_cmd.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void vprint_message(char *who_name, char *color, char *format, va_list ap) {
	char buf[512];
	buf[0] = '\0';

	strcat(buf, who_name);
	strcat(buf, "> ");

	print_color(buf, color, 0);
	vprintf(format, ap);
}

void print_message(char *who_name, char *color, char *format, int n, ...) {
	va_list ap;
	va_start(ap, n);

	vprint_message(who_name, color, format, ap);

	va_end(ap);
}

void print_dbg(char *format, int n, ...) {
	va_list ap;
	va_start(ap, n);

	vprint_message("dbg", COLOR_DBG, format, ap);

	va_end(ap);
}

void print_warning(char *format, int n, ...) {
	va_list ap;
	va_start(ap, n);

	vprint_message("warning", COLOR_WARNING, format, ap);

	va_end(ap);
}

void print_error(char *format, int n, ...) {
	va_list ap;
	va_start(ap, n);

	vprint_message("error", COLOR_ERROR, format, ap);

	va_end(ap);
}

void print_server(char *format, int n, ...) {
	va_list ap;
	va_start(ap, n);

	vprint_message("server", COLOR_SERVER, format, ap);

	va_end(ap);
}

void print_client(char *format, int n, ...) {
	va_list ap;
	va_start(ap, n);

	vprint_message("client", COLOR_CLIENT, format, ap);

	va_end(ap);
}