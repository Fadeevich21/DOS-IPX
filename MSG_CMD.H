#ifndef MSG_CMD_H
#define MSG_CMD_H

#include "prjct2\clr_prnt.h"

#define COLOR_DBG COLOR_CYAN
#define COLOR_WARNING COLOR_MAGENTA
#define COLOR_ERROR COLOR_RED
#define COLOR_SERVER COLOR_YELLOW
#define COLOR_CLIENT COLOR_GREEN

void print_message(char *who_name, char *color, char *format, int n, ...);

void print_dbg(char *format, int n, ...);
void print_warning(char *format, int n, ...);
void print_error(char *format, int n, ...);

void print_server(char* format, int n, ...);
void print_client(char *format, int n, ...);

#endif