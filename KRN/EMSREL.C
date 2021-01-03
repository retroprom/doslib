
#include <dos.h>

#include <krn/ems.h>
#include <krn/emsdefs.h>

int ems_release(int handle) {
	union REGS r;
	r.h.ah = EMS_REQ_RELEASE;
	r.x.dx = handle;
	int86(EMS_INT, &r, &r);
	if (r.h.ah) {
		return 1;
	}
	return 0;
}
