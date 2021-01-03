
#include <dos.h>

#include <hrn/hrn.h>
#include <hrn/hrnreg.h>

void hrn_bcfg_get(hrn_bank_t bank, hrn_bcfg_t *bcfg) {
	byte_t r0, r1, ra, mask;
	bool_t enable = TRUE, attrmem = FALSE;

	/* safety bailout */
	if(bank >= _hrn_bank_count) {
		return;
	}

	/* read the registers */
	r0 = hrn_reg_getb(HORNET_REG_BANK_xx_R0(bank));
	r1 = hrn_reg_getb(HORNET_REG_BANK_xx_R1(bank));
	ra = hrn_reg_getb(HORNET_REG_MEM_ATTRMEM);

	/* non-display banks have an enable flag in R1 */
	if(bank <= hrn_bank_c) {
		enable = (r1 & HORNET_BANK_xx_R1_ENABLE) ? TRUE : FALSE;
	}

	/* bank C is somewhat special */
	if(bank == hrn_bank_c) {
		/* bank C is 64k and has only 2 bits selector in R1 ... */
		mask = 0xC0;
		/* ... and one of those bits is the ATTR flag for the bank */
		attrmem = (r1 & HORNET_BANK_C_R1_ATTRMEM);
	} else {
		/* all other banks are 16k and have 4 bits selector in R1 ... */
		mask = 0xF0;
		/* ... and their ATTR flags are in the ATTRMEM register */
		if(bank < hrn_bank_c) {
			attrmem = (ra & (1<<bank));
		}
	}

	/* fill out the output structure */
	bcfg->bcfg_flags =
		(enable?HRN_BCFG_FLAG_ENABLE:0)
		|| (attrmem?HRN_BCFG_FLAG_ATTR:0);
	bcfg->bcfg_chip =
		(r1 & HORNET_BANK_xx_R1_CS_MASK)
		>> HORNET_BANK_xx_R1_CS_SHIFT;
	bcfg->bcfg_offset =
		((r1 << 8) | (r0 & mask)) >> 4;
}
