#ifndef DOSLIB_HRN_H
#define DOSLIB_HRN_H

#include <bsx/types.h>

/* Type for bank selection */
enum {
	hrn_bank_d0 = 0, hrn_bank_d1,
	hrn_bank_d2,     hrn_bank_d3,
	hrn_bank_e0,     hrn_bank_e1,
	hrn_bank_e2,     hrn_bank_e3,
	hrn_bank_c,
	hrn_bank_dm,     hrn_bank_fm,
	_hrn_bank_count
};
typedef uint8_t hrn_bank_t;

/* Type for chip selection */
enum {
	hrn_chip_rom = 0,
	hrn_chip_ram0, hrn_chip_ram1,
	hrn_chip_ram2, hrn_chip_ram3,
	hrn_chip_crd0, hrn_chip_crd1,
	_hrn_chip_count,
};
typedef uint8_t hrn_chip_t;

/* Structure for bank configurations */
#define HRN_BCFG_FLAG_ENABLE 0x01
#define HRN_BCFG_FLAG_ATTR   0x02
struct hrn_bcfg {
	byte_t     bcfg_flags;
	hrn_chip_t bcfg_chip;
	word_t     bcfg_offset;
};
typedef struct hrn_bcfg hrn_bcfg_t;

/* Structure for chip configurations */
#define HRN_CCFG_FLAG_WRITE  0x01
struct hrn_ccfg {
	byte_t  ccfg_flags;
};
typedef struct hrn_ccfg hrn_ccfg_t;

/* hrnstr.c */
extern const char *hrn_bank_name[11];
extern const char *hrn_chip_name[7];

/* hrnreg.c */
extern byte_t hrn_reg_getb(byte_t index);
extern void   hrn_reg_setb(byte_t index, byte_t value);

/* hrnbcget.c */
void hrn_bcfg_get(hrn_bank_t bank, hrn_bcfg_t *bcfg);
/* hrnbcset.c */
void hrn_bcfg_set(hrn_bank_t bank, const hrn_bcfg_t *bcfg);

#endif
