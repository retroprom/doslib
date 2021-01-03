/*
 * RDT variables
 *
 * Internal variables of the TSR library.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

rdt_state_t rdt_state;

bool_t  rdt_active = FALSE;
byte_t  rdt_request = 0;
bool_t  rdt_hotkey_flag = FALSE;
bool_t  rdt_timer_flag = FALSE;

krn_psp_t rdt_own_psp;
krn_dta_t rdt_own_dta;

krn_psp_t rdt_saved_psp;
krn_dta_t rdt_saved_dta;

#if RDT_CONFIG_COUNT_INT
word_t rdt_interrupt_idle = 0;
word_t rdt_interrupt_keyboard = 0;
word_t rdt_interrupt_timer = 0;
#endif

#if RDT_CONFIG_COUNT_EVT
word_t rdt_activate_enter = 0;
word_t rdt_activate_leave = 0;

word_t rdt_opportunity_calls = 0;
word_t rdt_opportunity_active = 0;
word_t rdt_opportunity_already = 0;
word_t rdt_opportunity_indos = 0;
word_t rdt_opportunity_spurious = 0;
word_t rdt_opportunity_taken = 0;
#endif
