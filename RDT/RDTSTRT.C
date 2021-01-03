/*
 * RDT start
 *
 * Call the TSR to start it interactively.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_start(const rdt_info_t *info) {
	int res;

	/* check presence */
	res = rdt_present(info);
	if(res) {
		goto err;
	}

	/* make the call */
	res = rdt_call(info, RDT_FUN_START,
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
