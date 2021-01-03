#ifndef GFX_H
#define GFX_H

#include <graphics.h>

#include "bsx.h"

extern bool_t gfxon;
extern int    gfxdriver;
extern int    gfxmode;
extern int    gfxw;
extern int    gfxh;

void gfxinit();
void gfxstop();

void gfxborders(
   int x, int y,
   int w, int h,
   direct_t d);

void gfxtxts();
void gfxtxtl();

void gfxtxtbox(
   int x, int y,
   direct_t direct,
   direct_t border,
   char *msg);

void gfxtxtboxf(
  int x, int y,
  direct_t direct,
  direct_t border,
  char *fmt, ...);

#endif /* GFX_H */
