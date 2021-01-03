/*
 * RDT unhook
 *
 * Internal function for unhooking and destroying the TSR.
 *
 * All handlers will be removed, all memory will be freed.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_unhook(void) {
	int ret = 0, res;
	krn_psp_ptr p = KRN_PSP_PTR(rdt_own_psp);

	/* remove service handler */
	res = rdt_serv_remove();
	if(res) {
		ret = res;
	}

	/* remove hook handlers */
	res = rdt_hook_remove();
	if(res) {
		ret = res;
	}

	/* free memory unless there was an error */
	if(!ret) {
		/* free environment */
		if(p->psp_envseg) {
			freemem(p->psp_envseg);
			p->psp_envseg = 0;
		}
		/* free memory */
		freemem(FP_SEG(p));
	}

	/* done */
	return ret;
}
