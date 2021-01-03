
#include <conio.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <bsx/cons.h>

void bail(char *msg) {
	fprintf(stderr, "Fatal: %s\n", msg);
	fflush(stderr);
	exit(1);
}

void bailf(char *fmt, ...) {
	va_list v;
	va_start(v, fmt);
	vfprintf(stderr, fmt, v);
	va_end(v);
	fflush(stderr);
	exit(1);
}

void pause(void) {
	fputs("Press any key\n", stderr);
	getch();
}
