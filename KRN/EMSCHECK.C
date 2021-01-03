
#include <dos.h>

#include <krn/ems.h>
#include <krn/emsdefs.h>

int ems_check(void) {
	int res;
	long handle;
	union REGS r;
	struct SREGS sr;
	/* open the EMS device */
	r.x.ax = 0x3D00;
	r.x.dx = (int)EMS_DRIVER;
	sr.ds  = _DS;
	intdosx(&r, &r, &sr);
	handle = r.x.ax;
	res = r.x.cflag;
	/* close the handle if we got one */
	if (!res) {
		r.h.ah = 0x3E;
		r.x.bx = handle;
		intdos(&r, &r);
	}
	/* if we could open then EMS is present */
	return res ? 1 : 0;
}
