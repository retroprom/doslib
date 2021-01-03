
#include <krn/krn.h>
#include <krn/dos.h>

void krn_psp_set(krn_psp_t psp) {
	union REGS r;
	r.h.ah = KRN_AH_SET_PSP;
	r.x.bx = psp;
	intdos(&r, &r);
}
