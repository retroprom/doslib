/*
 * RDT activation
 *
 * Activation is the process of switching context to the TSR so that we
 * can execute arbitrary code and most DOS system calls.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

void rdt_activate(void) {
	byte_t request = rdt_request;

	/* now considered active */
	rdt_active = TRUE;
	RDT_COUNT_EVT(rdt_activate_enter++);

	/* enable interrupts */
	_enable();

	/* switch to resident process */
	rdt_saved_psp = krn_psp_get();
	rdt_saved_dta = krn_dta_get();
	if(rdt_saved_psp != rdt_own_psp) {
		krn_psp_set(rdt_own_psp);
		krn_dta_set(rdt_own_dta);
	}

	/* install protection */
	rdt_prot_install();

	/* act on request */
	switch(request) {
	case RDT_FUN_START:
		/* run main function */
		if(rdt_state.rs_main) {
			rdt_state.rs_main();
		}
		break;
	case RDT_FUN_UNLOAD:
		/* perform unload */
		rdt_shutdown();
		break;
#if RDT_CONFIG_REPORT
	case RDT_FUN_REPORT:
		/* run report function */
		rdt_report();
		break;
#endif
	default:
		/* call slow handler */
		if(RDT_FUN_CALL_FIRST <= request
		   && request <= RDT_FUN_CALL_LAST) {
			if(rdt_state.rs_call) {
				rdt_state.rs_call(request, 0);
			}
		}
		break;
	}

	/* remove protection */
	rdt_prot_remove();

	/* restore interrupted process */
	if(rdt_saved_psp != rdt_own_psp) {
		krn_psp_set(rdt_saved_psp);
		krn_dta_set(rdt_saved_dta);
	}

	/* clean up */
	rdt_request = 0;
	rdt_hotkey_flag = FALSE;
	rdt_timer_flag = FALSE;

	/* no longer active */
	rdt_active = FALSE;
	RDT_COUNT_EVT(rdt_activate_leave++);

	/* perform unhook outside of process context */
	if(request == RDT_FUN_UNLOAD) {
		rdt_unhook();
	}
}
