
#include <krn/krn.h>
#include <krn/dos.h>

void krn_dta_set(krn_dta_t dta) {
	union REGS r;
	struct SREGS sr;
	r.h.ah = KRN_AH_SET_DTA;
	sr.ds  = FP_SEG(dta);
	r.x.dx = FP_OFF(dta);
	intdosx(&r, &r, &sr);
}
