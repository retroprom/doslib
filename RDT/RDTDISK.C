/*
 * RDT disk monitoring
 *
 * Can be used to prevent TSR activation during disk activity.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

static krn_intsav_t rdt_old_int13;

/* Disk interrupt
 *
 * Track transfers so we can wait for them.
 */
static void interrupt rdt_int13(void) {
	_chain_intr(rdt_old_int13);
}

/* Install disk access monitor
 */
int rdt_disk_install(void) {
	/* hook disk - monitor activity */
	krn_int_push(KRN_INT_DISK, &rdt_int13, &rdt_old_int13);
	/* done */
	return 0;
}

/* Remove disk access monitor
 */
int rdt_disk_remove(void) {
	int res;
	bool_t fail = FALSE;

	/* unhook disk - no more monitoring */
	res = krn_int_pop(KRN_INT_DISK, &rdt_int13, &rdt_old_int13);
	if(res) {
		fail = TRUE;
	}

	/* return status */
	return fail;
}
