#ifndef DOSLIB_EMS_H
#define DOSLIB_EMS_H

#include <bsx/types.h>

/* definitions */
#define EMS_VERSION_MAJ ((ems_version >> 4) & 0xF)
#define EMS_VERSION_MIN ((ems_version)      & 0xF)

/* emsvars.c */
extern int   ems_version;
extern int   ems_npages;
extern seg_t ems_pfseg;

/* emscheck.c */
extern int  ems_check(void);
/* emsinit.c */
extern int  ems_init(void);
/* emsalloc.c */
extern int  ems_allocate(int npages, int *handle);
/* emsmap.c */
extern int  ems_map(int handle, int phys, int page);
/* emsrel.c */
extern int  ems_release(int handle);

#endif
