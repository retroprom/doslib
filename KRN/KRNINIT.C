
#include <krn/krn.h>
#include <krn/dos.h>

int krn_init(void) {
	union REGS r;
	struct SREGS sr;
	byte_t far *p;

	r.x.ax = KRN_AX_GET_VERSION_OEM;
	intdos(&r, &r);
	krn_ver_maj = r.h.al;
	krn_ver_min = r.h.ah;
	krn_ver_oem = r.h.bh;

	r.h.ah = KRN_AH_GET_INDOS;
	intdosx(&r, &r, &sr);
	/* XXX derive SDA from INDOS on DOS3? */

	r.h.ah = KRN_AH_GET_IVR;
	intdosx(&r, &r, &sr);
	p = MK_FP(sr.es, r.x.bx);
	krn_ivr = (krn_ivr_t)(p - KRN_IVR_OFFSET);

	r.x.ax = KRN_AX_GET_SDA;
	intdosx(&r, &r, &sr);
	krn_sda = (krn_sda_t)MK_FP(sr.ds, r.x.si);

	return 0;
}
