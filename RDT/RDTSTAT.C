/*
 * RDT status
 */

#include <stdio.h>

#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

int rdt_status(const rdt_info_t *info) {
	int res = 0;
#if RDT_CONFIG_STATUS

	/* show basic info */
	printf("Program \"%s\" int %02x fun %02xh: ",
		   info->serv_name,
		   info->serv_interrupt,
		   info->serv_function);

	/* check presence */
	res = rdt_present(info);
	if(res) {
		printf("not present.\n");
		goto err_absent;
	}

#if RDT_CONFIG_REPORT
	printf("\n");
	/* perform the report call */
	res = rdt_call(info, RDT_FUN_REPORT,
				   0, 0, 0,
				   0, (byte_t far*)info->serv_name);
	if(res) {
		printf("  call failed.\n");
		goto err_status;
	}
#else
	printf("present.\n");
#endif

	/* done */
	return 0;

	/* error handling */
 err_status:
 err_absent:
#endif
	return res;
}
