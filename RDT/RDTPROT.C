/*
 * RDT protection
 *
 * This subsystem protects a TSR from destroying system state
 * by monitoring DOS calls and handling critical errors.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

/* Saved DOS service interrupt */
static krn_intsav_t rdt_old_int21;
/* Saved break handler */
static krn_intsav_t rdt_old_int23;
/* Saved critical handler */
static krn_intsav_t rdt_old_int24;

/* DOS service interrupt
 *
 * Protects the TSR from making bad calls.
 */
static void interrupt rdt_int21(krn_intreg_t r) {
  /* get function byte */
  byte_t ah = (r.ax >> 8) & 0xFF;
  /* functions below 0x0d are forbidden */
  if(ah < 0x0d) {
	r.ax = 0x00FF;
	return;
  }
  /* chain actual function */
  _chain_intr(rdt_old_int21);
}

/* Break handler
 *
 * Allows the TSR to catch break events.
 */
static void interrupt rdt_int23(void) {
  _chain_intr(rdt_old_int23);
}

/* Critical error handler
 *
 * Allows the TSR to catch critical errors.
 */
static void interrupt rdt_int24(void) {
  _chain_intr(rdt_old_int24);
}

/* Install protection functions
 *
 * Called when a TSR is activated for context switching.
 */
int rdt_prot_install(void) {
	int res = 0;

	/* install each handler in turn */
	res = krn_int_push(KRN_INT_CRITICAL,
						(krn_intfun_t)&rdt_int24,
						&rdt_old_int24);
	if(res) {
		goto err_int24;
	}
	res = krn_int_push(KRN_INT_BREAK,
						(krn_intfun_t)&rdt_int23,
						&rdt_old_int23);
	if(res) {
		goto err_int23;
	}
	res = krn_int_push(KRN_INT_SERVICE,
						(krn_intfun_t)&rdt_int21,
						&rdt_old_int21);
	if(res) {
		goto err_int21;
	}

	/* success */
	return 0;

	/* error handling */
 err_int21:
	krn_int_pop(KRN_INT_BREAK, &rdt_int23, &rdt_old_int23);
 err_int23:
	krn_int_pop(KRN_INT_CRITICAL, &rdt_int24, &rdt_old_int24);
 err_int24:
	return res;
}

/* Remove protection functions
 *
 * Called when leaving an active TSR context.
 */
int rdt_prot_remove(void) {
	int ret = 0, res;

	/* attempt to remove all handlers, remember errors */
	res = krn_int_pop(KRN_INT_SERVICE,
						(krn_intfun_t)&rdt_int21,
						&rdt_old_int21);
	if(res) {
		ret = res;
	}
	res = krn_int_pop(KRN_INT_BREAK,
						(krn_intfun_t)&rdt_int23,
						&rdt_old_int23);
	if(res) {
		ret = res;
	}
	res = krn_int_pop(KRN_INT_CRITICAL,
						(krn_intfun_t)&rdt_int24,
						&rdt_old_int24);
	if(res) {
		ret = res;
	}

	/* done */
	return ret;
}
