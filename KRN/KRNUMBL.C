
#include <krn/krn.h>
#include <krn/dos.h>

bool_t krn_umbl_get(void) {
	union REGS r;
	r.x.ax = KRN_AX_GET_UMB_LINK;
	intdos(&r, &r);
	return r.h.al;
}

int krn_umbl_set(bool_t link) {
	union REGS r;
	r.x.ax = KRN_AX_SET_UMB_LINK;
	r.x.bx = link;
	intdos(&r, &r);
	return (r.x.cflag) ? 1 : 0;
}
