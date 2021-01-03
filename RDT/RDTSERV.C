/*
 * RDT service
 *
 * This subsystem provides a multiplex interrupt handler
 * through which a TSR can be manipulated and called.
 */

#include <dos.h>
#include <string.h>

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

/* Saved multiplex handler */
static krn_intsav_t rdt_old_int2f;

/* Multiplex interrupt handler
 *
 * Request interface towards the TSR.
 */
static void interrupt rdt_int2f(krn_intreg_t r) {
	int res = 1;
	bool_t activate = FALSE;
	byte_t fun, sub;
	char far *id;
	char far *idr;

	/* get function codes */
	fun = (r.ax >> 8) & 0xFF;
	sub = (r.ax >> 0) & 0xFF;

	/* check the function code */
	if(fun != rdt_state.rs_info->serv_function) {
		goto chain;
	}

	/* check identity string if detecting */
	if(sub == RDT_FUN_DETECT) {
		id = (char far *)MK_FP(r.es, r.di);
		idr = (char far *)rdt_state.rs_info->serv_name;
		if(!id || !idr || _fstrncmp(id, idr, 8)) {
			goto chain;
		}
	}

	/* dispatch on the subfunction */
	switch(sub) {
	case RDT_FUN_DETECT:
		/* detect presence */
		res = 0;
		/* PSP in BX */
		r.bx = rdt_own_psp;
		/* return ident string */
		r.es = FP_SEG(rdt_state.rs_info->serv_name);
		r.di = FP_OFF(rdt_state.rs_info->serv_name);
		break;
	case RDT_FUN_UNLOAD:
	case RDT_FUN_REPORT:
	case RDT_FUN_START:
		activate = TRUE;
		break;
	default:
		if(RDT_FUN_FAST_FIRST <= sub
		   && sub <= RDT_FUN_FAST_LAST) {
			/* call fast handler */
			if(rdt_state.rs_fast) {
				res = rdt_state.rs_fast(sub, &r);
			}
		} else if(RDT_FUN_CALL_FIRST <= sub
				  && sub <= RDT_FUN_CALL_LAST) {
			/* activate for slow call */
			activate = TRUE;
		}
		break;
	}

	/* handle activation if required */
	if(activate) {
		/* request activation */
		if(!rdt_request) {
			rdt_request = sub;
		}
		/* only fail on changed request */
		if(rdt_request == sub) {
			res = 0;
		}
		/* provide activation opportunity */
		rdt_opportunity(1);
	}

	/* result code */
	r.ax = res;

	/* done */
	return;

 chain:
	/* chain handler */
	_chain_intr(rdt_old_int2f);
}

/* Install service handler
 */
int rdt_serv_install(void) {
	krn_int_push(0x2f, (krn_intfun_t)&rdt_int2f, &rdt_old_int2f);
	return 0;
}

/* Remove service handler
 */
int rdt_serv_remove(void) {
	int res = 0;
	bool_t fail = FALSE;

	res = krn_int_pop(0x2f, (krn_intfun_t)&rdt_int2f, &rdt_old_int2f);
	if(res) {
		fail = TRUE;
	}

	return fail;
}
