
#include <stdio.h>
#include <string.h>

#include <bsx/cons.h>
#include <bsx/opt.h>

#include <krn/krn.h>
#include <krn/dos.h>
#include <krn/ems.h>

static void dump_krn(void) {
	printf("\nKernel information\n\n");

	printf("  Version       : %d.%d (OEM %02X)\n\n",
		krn_ver_maj, krn_ver_min, krn_ver_oem);


	printf("  = SDA - DOS 3.x and up\n");
	printf("  SDA address   : %Fp\n", krn_sda);
	printf("  Flag CRITICAL : %u (%Fp)\n",
		krn_sda->sda_critical, &krn_sda->sda_critical);
	printf("  Flag INDOS    : %u (%Fp)\n",
		krn_sda->sda_indos, &krn_sda->sda_indos);

	printf("  = IVR - DOS 2.x and up\n");
	printf("  IVR address   : %Fp\n", krn_ivr);
	printf("  First MCB     : %Fp\n",
		krn_ivr->ivr_first_mcb);
	printf("  Device CLOCK  : %Fp\n",
		krn_ivr->ivr_clk_dhd);
	printf("  Device CON    : %Fp\n",
		krn_ivr->ivr_con_dhd);

	if(krn_ver_maj >= 4) {
		KRN_IVR_VERSION_DECL(ivr4p,dos4plus);
		char drive = '?';
		printf("  = IVR - DOS 4.x and up\n");
		if(ivr4p->ivr_bootdrive) {
			drive = '@' + ivr4p->ivr_bootdrive;
		}
		printf("  Boot drive    : %c\n",
			drive);
		printf("  Extended mem  : %u kB\n",
			ivr4p->ivr_extmem_kb);
		printf("  Disk buffers  : %u\n",
			ivr4p->ivr_buf_num);
		printf("  Cache buffers : %u\n",
			ivr4p->ivr_rabuf_num);
		printf("  Total blkdevs : %u\n",
			ivr4p->ivr_num_blkdev);
		printf("  Total drives  : %u\n",
			ivr4p->ivr_num_drives);
		printf("  Max seclen    : %u\n",
			ivr4p->ivr_maxseclen);
		printf("  Device NUL    : %Fp\n",
			&ivr4p->ivr_nul_dhd);
	}

	if(krn_ver_maj >= 5) {
		KRN_IVR_VERSION_DECL(ivr5p,dos5plus);
		printf("  = IVR - DOS 5.x and up\n");
		printf("  SETVER list   : %Fp\n",
			ivr5p->ivr_setver_list);
		printf("  A20FIX offset : %04x\n",
			ivr5p->ivr_a20fix_off);
		printf("  Newest PSP    : %04x\n",
			ivr5p->ivr_newest_psp);
	}
}

static void dump_dhd(void) {
	krn_dhd_t dhd;

	printf("\nDriver information\n");

	printf("\n  DHD\n", dhd);
	dhd = krn_dhd_get_first();
	while(dhd) {
		printf("  %Fp\n", dhd);
		dhd = krn_dhd_get_next(dhd);
	}
}

static void dump_psp(void) {
	krn_psp_t psp;
	krn_dta_t dta;
	krn_psp_ptr pspp;
	size_t sz;

	psp = krn_psp_get();
	if (!psp) {
		bail("Could not get PSP");
	}

	dta = krn_dta_get();
	if(!dta) {
		bail("Could not get DTA");
	}

	printf("\nProcess information\n\n");

	printf("  Current PSP : %04X\n", psp);
	printf("  Current DTA : %Fp\n", dta);

	printf("\n  PSP  ENV  END  PARENT ARGS\n");
	psp = krn_psp_get();
	while(psp) {
		pspp = KRN_PSP_PTR(psp);
		printf("  %04X %04x %04x %04x   ",
		       psp, pspp->psp_envseg, pspp->psp_endseg, pspp->psp_parent);
		sz = strcspn(pspp->psp_args, "\r\n");
		fwrite(pspp->psp_args, 1, sz, stdout);
		printf("\n");
		psp = krn_psp_get_parent(psp);
	}
}

static void dump_mcb(void) {
	int res = 0;
	bool_t ul = FALSE;
	krn_mcb_t mcb;

	printf("\nMemory information\n");

	ul = krn_umbl_get();
	if(!ul) {
		res = krn_umbl_set(TRUE);
		if(!res) {
			ul = TRUE;
		}
	}

	printf("\n  R MCB  PSP    LEN   SIZE\n");

	mcb = krn_mcb_get_first();
	while(mcb) {
		char reg;
		krn_psp_t psp;
		krn_psp_ptr pspp;
		krn_mcb_ptr mcbp = KRN_MCB_PTR(mcb);
		if(mcb > 40960) {
			reg = 'u';
		} else {
			reg = ' ';
		}
		psp = mcbp->mcb_psp;
		printf("  %c %04x %04x %5u %6lu ",
			   reg, mcb, psp, mcbp->mcb_size, (unsigned long)mcbp->mcb_size * 16);
		if(psp == 0) {
			printf("free\n");
		} else if(psp == 8) {
			printf("kernel\n");
		} else {
			printf("process\n");
		}
		mcb = krn_mcb_get_next(mcb);
	}

	if(ul) {
		krn_umbl_set(ul);
	}
}

static void dump_ems(void) {
	int res;

	res = ems_check();
	if (res) {
		bail("EMS not present");
	}

	res = ems_init();
	if (res) {
		bailf("EMS init failed: %d", res);
	}

	printf("\nEMS information\n\n");

	printf("  Version    : %d.%d\n",
		   EMS_VERSION_MAJ,
		   EMS_VERSION_MIN);
	printf("  Page frame : %x\n", ems_pfseg);
	printf("  Pages      : %d\n", ems_npages);
}

static void dump_int(void) {
}

opt_t opts[10] = {
	{'/',OPT_FLAG_CATEGORY, "GENERAL",
	 "General options"},
	{'?',OPT_FLAG_NONE, "/?",
	 "Show help"},
	{'/',OPT_FLAG_CATEGORY, "SYSINFO",
	 "System information"},
	{'a',OPT_FLAG_NONE, "/a",
	 "Dump all information"},
	{'k',OPT_FLAG_NONE, "/k",
	 "Dump kernel information"},
	{'d',OPT_FLAG_NONE, "/d",
	 "Dump driver information"},
	{'p',OPT_FLAG_NONE, "/p",
	 "Dump process information"},
	{'m',OPT_FLAG_NONE, "/m",
	 "Dump memory information"},
	{'e',OPT_FLAG_NONE, "/e",
	 "Dump EMS information"},
	{'i',OPT_FLAG_NONE, "/i",
	 "Dump interrupt information"},
};

int main(int argc, char **argv) {
	int res = 0;
	byte_t do_count = 0;
	bool_t do_krn = 0,
		do_int = 0, do_mcb = 0,
		do_dhd = 0, do_psp = 0,
		do_ems = 0;

	opt_start(10, opts, argc, argv);
	while((res = opt_parse()) > 0) {
		switch(res) {
		case 'a':
			do_count++;
			do_krn = TRUE;
			do_int = TRUE;
			do_mcb = TRUE;
			do_ems = TRUE;
			do_dhd = TRUE;
			do_psp = TRUE;
			break;
		case 'k':
			do_count++;
			do_krn = TRUE;
			break;
		case 'i':
			do_count++;
			do_int = TRUE;
			break;
		case 'm':
			do_count++;
			do_mcb = TRUE;
			break;
		case 'e':
			do_count++;
			do_ems = TRUE;
			break;
		case 'c':
			do_count++;
			do_dhd = TRUE;
			break;
		case 'p':
			do_count++;
			do_psp = TRUE;
			break;
		case '?':
			opt_usage(0,0);
			return 0;
		default:
			continue;
		}
	}
	if(res < 0) {
		opt_usage(0,0);
		return 1;
	}
	opt_finish();

	if(do_count == 0) {
		do_krn = 1;
		do_dhd = 1;
		do_psp = 1;
	}

	res = krn_init();
	if (res) {
		bail("DOS incompatible");
	}

	if(do_krn) {
		dump_krn();
	}
	if(do_dhd) {
		dump_dhd();
	}
	if(do_psp) {
		dump_psp();
	}
	if(do_mcb) {
		dump_mcb();
	}
	if(do_ems) {
		dump_ems();
	}
	if(do_int) {
		dump_int();
	}

	return 0;
}
