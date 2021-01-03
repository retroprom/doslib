/*
 * RDT installation
 *
 * Installs the current process as a TSR.
 *
 * Will establish a service interrupt as well as any hooks required for activation.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_install(const rdt_info_t *info) {
	int res;

	/* check if already present */
	res = rdt_present(info);
	if(!res) {
		res = 1;
		goto err_present;
	}

	/* initialize state */
	rdt_state.rs_info = info;
	rdt_own_psp = krn_psp_get();
	rdt_own_dta = krn_dta_get();

	/* install hook handlers */
	res = rdt_hook_install();
	if(res) {
		goto err_hook;
	}

	/* install service handler */
	res = rdt_serv_install();
	if(res) {
		goto err_serv;
	}

	/* done */
	return 0;

	/* error handling */
 err_serv:
	rdt_hook_remove();
 err_hook:
 err_present:
	return res;
}
