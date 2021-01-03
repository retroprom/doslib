/*
 * RDT call interface
 *
 * Interface for placing calls to a resident TSR.
 */

#include <dos.h>

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_call(const rdt_info_t *info,
			 byte_t subfunc,
			 word_t *w1,
			 word_t *w2,
			 word_t *w3,
			 byte_t far *p1,
			 byte_t far *p2) {
	union REGS r;
	struct SREGS sr;

	/* function codes */
	r.h.ah = info->serv_function;
	r.h.al = subfunc;
	/* word arguments */
	r.x.bx = w1 ? *w1 : 0;
	r.x.cx = w2 ? *w2 : 0;
	r.x.dx = w3 ? *w3 : 0;
	/* pointer arguments */
	sr.ds  = FP_SEG(p1);
	r.x.si = FP_OFF(p1);
	sr.es  = FP_SEG(p2);
	r.x.di = FP_OFF(p2);

	/* perform the call */
	int86x(info->serv_interrupt, &r, &r, &sr);

	/* process returns */
	if(w1) { *w1 = r.x.bx; }
	if(w2) { *w2 = r.x.cx; }
	if(w3) { *w3 = r.x.dx; }

	/* return result code */
	return (int)r.x.ax;
}
