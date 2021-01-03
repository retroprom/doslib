
#include <krn/krn.h>
#include <krn/dos.h>

krn_dta_t krn_dta_get(void) {
	union REGS r;
	struct SREGS sr;
	r.h.ah = KRN_AH_GET_DTA;
	intdosx(&r, &r, &sr);
	return MK_FP(sr.es, r.x.bx);
}
