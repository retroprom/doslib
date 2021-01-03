
#include <stdio.h>

#include <bsx/cons.h>

#include <krn/ems.h>

void dump_info (void) {
	printf("\n");
	printf("EMS detected\n");
	printf("  Version    : %d.%d\n",
			EMS_VERSION_MAJ,
			EMS_VERSION_MIN);
	printf("  Page frame : %x\n", ems_pfseg);
	printf("  Pages      : %d\n", ems_npages);
}

int test (int npages) {
	int res = 0, i;
	int handle;

	printf("\n");
	printf("Running EMS test...\n");

	/* allocate some memory */
	printf("  Allocating %d pages...", npages);
	res = ems_allocate(npages, &handle);
	if (res) {
		printf("failed\n");
		goto out_return;
	}
	printf("done\n");

	/* map some of it */
	for (i = 0; i < npages; i++) {
		int phys = i % 4;
		printf("  Mapping page %d at frame %d...", i, phys);
		res = ems_map(handle, phys, i);
		if (res) {
			printf("failed\n");
			goto out_release;
		}
		printf("done\n");
	}

out_release:
	/* clean up by releasing the memory */
	printf("  Releasing memory...");
	res = ems_release(handle);
	if (res) {
		printf("failed\n");
		goto out_return;
	}
	printf("done\n");

	/* finish output */
	printf("done.\n");

 out_return:
	return res;
}

int main (int argc, char **argv) {
	int i, res, version, npages;
	long handle;

	res = ems_check();
	if (res) {
		bail("EMS not present");
	}

	res = ems_init();
	if (res) {
		bailf("EMS init failed: %d", res);
	}

	dump_info();

	res = test(8);
	if (res) {
		bail("EMS test failed");
	}

	return 0;
}
