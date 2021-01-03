/*
 * RDT execution hook
 *
 * Contains interrupt handlers used for activation opportunities.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

static krn_intsav_t rdt_old_int08;
static krn_intsav_t rdt_old_int28;

/* Timer interrupt
 *
 * Scheduling opportunity.
 */
static void interrupt rdt_int08(void) {
	RDT_COUNT_INT(rdt_interrupt_timer++);
	rdt_old_int08();
	if(!rdt_active) {
		rdt_opportunity(0);
	}
}

/* DOS idle interrupt
 *
 * Scheduling opportunity.
 */
static void interrupt rdt_int28(void) {
	RDT_COUNT_INT(rdt_interrupt_idle++);
	if(!rdt_active) {
		rdt_opportunity(1);
	}
	_chain_intr(rdt_old_int28);
}

/* Install hook handlers
 */
int rdt_hook_install(void) {
	/* hook idle - ready for activation */
	krn_int_push(KRN_INT_IDLE, &rdt_int28, &rdt_old_int28);
	/* hook timer - ready for activation */
	krn_int_push(KRN_INT_TIMER, &rdt_int08, &rdt_old_int08);
	/* done */
	return 0;
}

/* Remove hook handlers
 */
int rdt_hook_remove(void) {
	int res;
	bool_t fail = FALSE;

	/* unhook timer - no more timer */
	res = krn_int_pop(KRN_INT_TIMER, &rdt_int08, &rdt_old_int08);
	if(res) {
		fail = TRUE;
	}
	/* unhook idle - no more activation */
	res = krn_int_pop(KRN_INT_IDLE, &rdt_int28, &rdt_old_int28);
	if(res) {
		fail = TRUE;
	}

	/* return status */
	return fail;
}
