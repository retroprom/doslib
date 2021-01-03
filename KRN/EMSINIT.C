
#include <dos.h>

#include <krn/ems.h>
#include <krn/emsdefs.h>

int ems_init(void) {
	union REGS r;
	int res, version, npages;
	seg_t pfseg;

	/* check EMS present */
	res = ems_check();
	if (res) {
		res = 1;
		goto out;
	}

	/* check EMS version */
	r.h.ah = EMS_REQ_VERSION;
	int86(EMS_INT, &r, &r);
	if (r.h.ah) {
		res = 2;
		goto out;
	}
	version = (int)r.h.al;
	if (version < EMS_MIN_VERSION) {
		res = 3;
		goto out;
	}

	/* check EMS status */
	r.h.ah = EMS_REQ_GET_MSTAT;
	int86(EMS_INT, &r, &r);
	if (r.h.ah) {
		res = 4;
		goto out;
	}

	/* get number of EMS pages */
	r.h.ah = EMS_REQ_GET_NPAGES;
	int86(EMS_INT, &r, &r);
	if (r.h.ah) {
		res = 5;
		goto out;
	}
	npages = (int)r.x.bx;

	/* get EMS page frame segment */
	r.h.ah = EMS_REQ_GET_PFSEG;
	int86(EMS_INT, &r, &r);
	if (r.h.ah) {
		res = 6;
		goto out;
	}
	pfseg = r.x.bx;

	/* remember various things */
	ems_version = version;
	ems_npages = npages;
	ems_pfseg = pfseg;

 out:
	/* done */
	return res;
}
