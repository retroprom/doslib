#ifndef RDT_RDTPRIV_H
#define RDT_RDTPRIV_H

#include <krn/dos.h>
#include <krn/krn.h>
#include <rdt/rdt.h>
#include <rdt/rdtconf.h>

enum {
	state_ready = 0,
	state_hooking,
	state_hooked,
	state_activating,
	state_active,
	state_deactivating,
	state_unhooking,
	state_unhooked,
};

/**************************************** rdtvars.c */

/* true when the TSR is active */
extern bool_t rdt_active;

/* request activating the TSR */
extern byte_t rdt_request;

/* set to activate the TSR by hotkey */
extern bool_t rdt_hotkey_flag;
/* set to activate the TSR by timer */
extern bool_t rdt_timer_flag;

/* own process state - swapped in while active */
extern krn_psp_t rdt_own_psp;
extern krn_dta_t rdt_own_dta;
extern krn_stk_t rdt_own_stack;

/* saved process state - restored when leaving active */
extern krn_psp_t rdt_saved_psp;
extern krn_dta_t rdt_saved_dta;
extern krn_stk_t rdt_saved_stack;

#if RDT_CONFIG_COUNT_INT
extern word_t rdt_interrupt_idle;
extern word_t rdt_interrupt_keyboard;
extern word_t rdt_interrupt_timer;
#define RDT_COUNT_INT(expr) expr
#else
#define RDT_COUNT_INT(expr)
#endif

#if RDT_CONFIG_COUNT_INT
extern word_t rdt_activate_enter;
extern word_t rdt_activate_leave;

extern word_t rdt_opportunity_calls;
extern word_t rdt_opportunity_active;
extern word_t rdt_opportunity_already;
extern word_t rdt_opportunity_indos;
extern word_t rdt_opportunity_spurious;
extern word_t rdt_opportunity_taken;
#define RDT_COUNT_EVT(expr) expr
#else
#define RDT_COUNT_EVT(expr)
#endif

/**************************************** rdtacti.c */
extern void rdt_activate(void);

/**************************************** rdtshut.c */
extern int rdt_shutdown(void);

/**************************************** rdtoppt.c */
extern int rdt_opportunity(byte_t doslim);

/**************************************** rdtrept.c */
#if RDT_CONFIG_REPORT
extern void rdt_report(void);
#endif

/**************************************** rdtunhk.c */
extern int rdt_unhook(void);

/**************************************** rdthook.c */
extern int rdt_hook_install(void);
extern int rdt_hook_remove(void);

/**************************************** rdtprot.c */
extern int rdt_prot_install(void);
extern int rdt_prot_remove(void);

/**************************************** rdtserv.c */
extern int rdt_serv_install(void);
extern int rdt_serv_remove(void);

#endif
