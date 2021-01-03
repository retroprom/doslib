
#include <hrn/hrn.h>
#include <hrn/hrnreg.h>

void hrn_bcfg_set(hrn_bank_t bank, const hrn_bcfg_t *bcfg) {
	byte_t r0, r1, ra;

	/* safety bailout */
	if(bank >= _hrn_bank_count) {
		return;
	}

	hrn_reg_setb(HORNET_REG_BANK_xx_R0(bank), r0);
	hrn_reg_setb(HORNET_REG_BANK_xx_R1(bank), r1);
	if(bank < hrn_bank_c) {
		/* XXX is this correct for all banks ? */
		/* XXX don't we need to update instead of plain set? */
		hrn_reg_setb(HORNET_REG_MEM_ATTRMEM, ra);
	}
}
