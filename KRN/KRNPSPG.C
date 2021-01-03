
#include <krn/krn.h>
#include <krn/dos.h>

krn_psp_t krn_psp_get(void) {
	union REGS r;
	r.h.ah = KRN_AH_GET_PSP;
	intdos(&r, &r);
	return r.x.bx;
}
