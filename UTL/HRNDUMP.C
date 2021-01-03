
#include <dos.h>
#include <stdio.h>

#include <stdio.h>

#include <hrn/hrn.h>

int main(int argc, char **argv) {
	hrn_bank_t b;
	hrn_bcfg_t bc;
	for(b = 0; b < _hrn_bank_count; b++) {
		hrn_bcfg_get(b, &bc);
		printf("Bank %s chip %s offset 0x%04X%s%s\n",
				hrn_bank_name[b],
				hrn_chip_name[bc.bcfg_chip],
				bc.bcfg_offset,
				(bc.bcfg_flags&HRN_BCFG_FLAG_ENABLE)?" enabled":"",
				(bc.bcfg_flags&HRN_BCFG_FLAG_ATTR)?" attrmem":"");
	}
	return 0;
}
