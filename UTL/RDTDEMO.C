
#include <bsx/cons.h>

#include <krn/krn.h>
#include <krn/dos.h>
#include <rdt/rdt.h>
#include <rdt/rdtpriv.h>

#include <alloc.h>
#include <conio.h>
#include <dos.h>
#include <string.h>

const rdt_info_t info = {0x2F, 0x87, "RDTDEMO"};

static int r_fast(byte_t func, krn_intreg_t *regs) {
	return 0;
}

static int r_call(byte_t func, krn_intreg_t *regs) {
	printf("Call %xh\n", func);
	fflush(stdout);
	return 0;
}

static int r_main(void) {
	printf("Main\n");
	fflush(stdout);
	return 0;
}

int main(int argc, char **argv) {
	int res;

	char *action = "status";
	if(argc > 1) {
		action = argv[1];
	}

	res = krn_init();
	if(res) {
		bail("Could not init KRN");
	}

	rdt_state.rs_main = &r_main;
	rdt_state.rs_fast = &r_fast;
	rdt_state.rs_call = &r_call;

	if(!strcmp(action, "install")) {
		printf("Installing RDT...\n");
		res = rdt_install(&info);
		if(res) {
			bail("Could not install RDT");
		}
		rdt_status(&info);
		keep(0, 8192);
	} else if(!strcmp(action, "start")) {
		printf("Starting RDT...\n");
		res = rdt_start(&info);
		if(res) {
			bail("Failed to start RDT");
		}
	} else if(!strcmp(action, "uninstall")) {
		printf("Uninstalling RDT...\n");
		res = rdt_uninstall(&info);
		if(res) {
			bail("Failed to remove RDT");
		}
	} else {
		rdt_status(&info);
	}

	return 0;
}
