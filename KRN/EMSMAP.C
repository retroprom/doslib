
#include <dos.h>

#include <krn/ems.h>
#include <krn/emsdefs.h>

int ems_map(int handle, int phys, int page) {
	union REGS r;
	r.h.ah = EMS_REQ_MAP;
	r.h.al = phys;
	r.x.bx = page;
	r.x.dx = handle;
	int86(EMS_INT, &r, &r);
	if (r.h.ah) {
		return 1;
	}
	return 0;
}
