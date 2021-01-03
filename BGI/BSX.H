#ifndef BASICS_H
#define BASICS_H

typedef char bool_t;
#define FALSE ((bool_t)0)
#define TRUE  ((bool_t)1)

typedef enum {
    CENTER = 0x00,
    NORTH  = 0x01,
    EAST   = 0x02,
    SOUTH  = 0x04,
    WEST   = 0x08,
    OMNI   = 0x0F
} direct_t;

void bail(char *msg);
void bailf(char *fmt, ...);

void pause();

#endif /* BASICS_H */
