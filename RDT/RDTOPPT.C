/*
 * RDT activation opportunity
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_opportunity(byte_t doslim) {
	rdt_cause_t cause = RDT_CAUSE_NONE;

	_disable();

	RDT_COUNT_EVT(rdt_opportunity_calls++);

	/* abort if already active */
	if(rdt_active) {
		RDT_COUNT_EVT(rdt_opportunity_already++);
		goto out;
	}

	/* determine activation cause */
	if(rdt_timer_flag) cause = RDT_CAUSE_TIMER;
	if(rdt_hotkey_flag) cause = RDT_CAUSE_HOTKEY;
	if(rdt_request) cause = RDT_CAUSE_REQUEST;

	/* abort if not requested */
	if(!cause) {
		RDT_COUNT_EVT(rdt_opportunity_spurious++);
		goto out;
	}

	/* abort if in DOS call or error */
	if((KRN_INDOS >= doslim) || KRN_CRITICAL) {
		RDT_COUNT_EVT(rdt_opportunity_indos++);
		goto out;
	}

	/* count as taken */
	RDT_COUNT_EVT(rdt_opportunity_taken++);

	/* activate the program */
	rdt_activate();

	/* done */
	return 0;
 out:
	/* re-enable interrupts */
	_enable();
	/* not doing anything */
	return 1;
}
