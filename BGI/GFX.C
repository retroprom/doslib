
#include "gfx.h"

#include <stdio.h>
#include <stdarg.h>

bool_t gfxon = FALSE;
int    gfxdriver;
int    gfxmode;
int    gfxw;
int    gfxh;

char fmtbuf[256];

void gfxinit() {
   int res;

   gfxdriver = CGA;
   gfxmode = CGAHI;

   initgraph(&gfxdriver, &gfxmode, "a:\\tc\\bgi");
   res = graphresult();
   if (res != grOk)
      bail("Could not initialize graphics");

   gfxon = TRUE;

   gfxw = getmaxx();
   gfxh = getmaxy();

   setcolor(getmaxcolor());
}

void gfxstop() {
   if (gfxon) {
      closegraph();
      gfxon = FALSE;
   }
}

void gfxborders(
	  int x, int y,
	  int w, int h,
	  direct_t d) {
   if (d&NORTH) {
      line(x, y, x + w, y);
   }
   if (d&EAST) {
      line(x, y, x, y + h);
   }
   if (d&SOUTH) {
      line(x, y + h, x + w, y + h);
   }
   if (d&WEST) {
      line(x + w, y, x + w, y + h);
   }
}

void gfxtxts() {
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
}

void gfxtxtl() {
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
}

void gfxtxtbox(
  int x, int y,
  direct_t direct,
  direct_t border,
  char *msg) {
  int w = textwidth(msg);
  int h = textheight(msg);
  if (direct&NORTH) {
    y -= h + 2;
  } else if (direct&SOUTH) {
    y = y;
  } else {
    y -= (h + 2) / 2;
  }
  if (direct&EAST) {
    x = x;
  } else if (direct&WEST) {
    x -= w + 2;
  } else {
    x -= (w + 2) / 2;
  }
  gfxborders(x, y, w + 2, h + 2, border);
  outtextxy(x + 2, y + 2, msg);
}

void gfxtxtboxf(
  int x, int y,
  direct_t direct,
  direct_t border,
  char *fmt, ...) {
  va_list v;
  va_start(v, fmt);
  vsprintf(fmtbuf, fmt, v);
  va_end(v);
  gfxtxtbox(x, y, direct, border, fmtbuf);
}
