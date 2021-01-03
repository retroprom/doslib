/*
 * RDT shutdown
 *
 * Internal function for shutting down the TSR.
 *
 * The runtime will be finalized.
 *
 * Must be called in process context.
 */

#include <process.h>

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_shutdown(void) {
	/* call runtime exit */
	_cexit();
	/* done */
	return 0;
}
