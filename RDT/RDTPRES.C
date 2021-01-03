/*
 * RDT presence check
 *
 * Check if the given RDT is present as a TSR.
 */

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_present(const rdt_info_t *info) {
	return rdt_call(info, RDT_FUN_DETECT,
					0, 0, 0,
					0, (byte_t far*)info->serv_name);
}
