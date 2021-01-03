
#include "bsx.h"

#ifdef GFX
#include "gfx.h"
#endif

#include <stdio.h>
#include <stdarg.h>

void bail(char *msg) {
#ifdef GFX
   gfxstop();
#endif
   printf("Fatal: %s\n", msg);
   pause();
   exit(1);
}

void bailf(char *fmt, ...) {
   va_list v;
#ifdef GFX
   gfxstop();
#endif
   printf("Fatal: ");
   va_start(v, fmt);
   vprintf(fmt, v);
   va_end(v);
   printf("\n");
   pause();
   exit(1);
}

void pause() {
#ifdef GFX
	if(gfxon) {
		gfxtxts();
		gfxtxtbox(gfxw / 2, gfxh, NORTH, NORTH|EAST|WEST, "Press any key");
	} else {
		puts("Press any key");
	}
#else
	puts("Press any key");
#endif
	getch();
}
