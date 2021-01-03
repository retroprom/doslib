
#include <stdio.h>
#include <stdarg.h>
#include <graphics.h>

#define GFX

#include "gfx.h"

int main(int argc, char **argv) {
   char *gdn;
   char *gmn;
   int qw, qh;

   initgfx();

   gdn = getdrivername();
   gmn = getmodename(getgraphmode());
   qw = gfxw / 4;
   qh = gfxh / 4;

   textlarge();
   textbox(qw * 2, qh * 1, CENTER, OMNI, "MXXX Test XXXM");
   textsmall();
   textboxf(qw * 2, qh * 3, CENTER, OMNI, "Graphics %s", gdn);
   pause();

   stopgfx();

   printf("Driver <%s> mode <%s>\n", gdn, gmn);

   return 0;
}
