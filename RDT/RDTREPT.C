
#include <stdio.h>

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

#if RDT_CONFIG_REPORT
void rdt_report(void) {
	printf("  resident psp=%xh dta=%xh\n",
		   rdt_own_psp, rdt_own_dta);
	if(rdt_active) {
		printf("  saved psp=%xh dta=%xh\n",
			   rdt_saved_psp, rdt_saved_dta);
	}
	printf("  %s request=%02xh\n",
		   rdt_active?"active":"inactive", rdt_request);
#if RDT_CONFIG_COUNT_INT
	printf("  ints idle=%u keyboard=%u timer=%u\n",
		   rdt_interrupt_idle, rdt_interrupt_keyboard, rdt_interrupt_timer);
#endif
#if RDT_CONFIG_COUNT_EVT
	printf("  activate enter=%u leave=%u\n",
		   rdt_activate_enter, rdt_activate_leave);
	printf("  opportunity calls=%u active=%u already=%u indos=%u spurious=%u taken=%u\n",
		   rdt_opportunity_calls, rdt_opportunity_active,
		   rdt_opportunity_already, rdt_opportunity_indos,
		   rdt_opportunity_spurious, rdt_opportunity_taken);
#endif
}
#endif
