
#include <krn/krn.h>
#include <krn/dos.h>

void krn_idle(void) {
	union REGS r;
	int86(KRN_INT_IDLE, &r, &r);
}
