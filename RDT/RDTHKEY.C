/*
 * RDT hotkey support
 *
 * Can be used to launch the TSR using a keyboard hotkey.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

static krn_intsav_t rdt_old_int09;

/* Keyboard interrupt
 *
 * Detect hotkeys and request launch.
 */
static void interrupt rdt_int09(void) {
	RDT_COUNT_INT(rdt_interrupt_keyboard++);
	rdt_old_int09();
}

/* Install hotkey handler
 */
int rdt_hkey_install(void) {
	/* hook keyboard - monitor hotkey */
	krn_int_push(KRN_INT_KEYBOARD, &rdt_int09, &rdt_old_int09);
	return 0;
}

/* Remove hotkey handler
 */
int rdt_hkey_remove(void) {
	int res;
	bool_t fail = FALSE;

	/* unhook keyboard - no more hotkey */
	res = krn_int_pop(KRN_INT_KEYBOARD, &rdt_int09, &rdt_old_int09);
	if(res) {
		fail = TRUE;
	}

	/* return status */
	return fail;
}
