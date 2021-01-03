/*
 * RDT uninstall
 *
 * Client-level function for removing an installed TSR.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_uninstall(const rdt_info_t *info) {
	int res = 0;

	/* check presence */
	res = rdt_present(info);
	if(res) {
		goto err;
	}

	/* perform the call */
	res = rdt_call(info, RDT_FUN_UNLOAD,
				   0, 0, 0, 0, 0);
	if(res) {
		goto err;
	}

	/* done */
	return 0;

	/* error handling */
 err:
	return res;
}
