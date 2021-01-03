
#include <dos.h>

#include <krn/ems.h>
#include <krn/emsdefs.h>

int ems_allocate(int npages, int *handle) {
	union REGS r;
	r.h.ah = EMS_REQ_ALLOCATE;
	r.x.bx = npages;
	int86(EMS_INT, &r, &r);
	if (r.h.ah) {
		return 1;
	}
	*handle = (int)r.x.dx;
	return 0;
}
