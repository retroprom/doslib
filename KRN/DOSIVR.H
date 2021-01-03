#ifndef KRN_IVRDEF_H
#define KRN_IVRDEF_H

#include <krn/dosdhd.h>
#include <krn/dosdpb.h>

/* Our IVR begins before the actual one
 * so that we can include ivr_first_mcb.
 *
 * Since there only is one IVR and the
 * relationship between these fields
 * is fixed, this should be okay.
 *
 * XXX How backward-compatible is this?
 */
#define KRN_IVR_OFFSET (0x02)

/* Reference to version-specific IVR structure
 */
#define KRN_IVR_VERSION_REF(version) \
	krn_ivr->ivr_version.ivr_##version
/* Get pointer to version-specific IVR structure
 */
#define KRN_IVR_VERSION_PTR(version) \
	(&krn_ivr->ivr_version.ivr_##version)
/* Declare pointer to version-specific IVR structure
 */
#define KRN_IVR_VERSION_DECL(name,version) \
	struct krn_ivr_##version far *name = \
		KRN_IVR_VERSION_PTR(version)

#pragma pack(push,1)
/* IVR fields specific to DOS 4.x */
struct krn_ivr_dos4 {
	/* 10*/ byte_t         _ivr_dos4_compat[0x27];
	/* 37*/ byte_t far     *ivr_ifs_entry;
	/* 3B*/ byte_t far     *ivr_ifs_first;
	/* 3F*/ /* continued in dos4plus */
};
/* IVR fields specific to DOS 4.x and up */
struct krn_ivr_dos4plus {
	/* 10*/ word_t          ivr_maxseclen;
	/* 12*/ byte_t far     *ivr_dbi;
	/* 16*/ byte_t far     *ivr_cds;
	/* 1A*/ byte_t far     *ivr_fcbs;
	/* 1E*/ word_t          ivr_fcbs_numprot;
	/* 20*/ byte_t          ivr_num_blkdev;
	/* 21*/ byte_t          ivr_num_drives;
	/* 22*/ struct krn_dhd  ivr_nul_dhd;
	/* 34*/ byte_t          ivr_numjoined;
	/* 35*/ word_t         _ivr_dos4plus_unknown;
	/* 37*/ byte_t         _ivr_dos4plus_compat[0x08];
	/* 3F*/ word_t          ivr_buf_num;
	/* 41*/ word_t          ivr_rabuf_num;
	/* 43*/ byte_t          ivr_bootdrive;
	/* 44*/ byte_t          ivr_use_dmove;
	/* 45*/ word_t          ivr_extmem_kb;
	/* 47*/
};
/* IVR fields specific to DOS 5.x and up */
struct krn_ivr_dos5plus {
	/* 10*/ byte_t         _ivr_dos5plus_compat[0x27];
	/* 37*/ byte_t far     *ivr_setver_list;
	/* 3B*/ word_t          ivr_a20fix_off;
	/* 3D*/ krn_psp_t       ivr_newest_psp;
	/* 3F*/ /* continued in dos4plus */
};
/* IVR fields specific to DOS 7.x */
struct krn_ivr_dos7 {
	/* 10*/ byte_t         _ivr_dos7_compat[0x37];
	/* 47*/ byte_t         _ivr_dos7_unknown[0x19];
	/* 60*/ byte_t          ivr_dos_flag;
	/* 61*/
};
/* Generalized IVR structure */
struct krn_ivr {
	/*-02*/ krn_mcb_t           ivr_first_mcb;
	/* 00*/ struct krn_dpb far *ivr_first_dpb;
	/* 04*/ byte_t far         *ivr_first_sft;
	/* 08*/ krn_dhd_t           ivr_clk_dhd;
	/* 0C*/ krn_dhd_t           ivr_con_dhd;
	/* 10*/
		union {
			struct krn_ivr_dos4     ivr_dos4;
			struct krn_ivr_dos4plus ivr_dos4plus;
			struct krn_ivr_dos5plus ivr_dos5plus;
			struct krn_ivr_dos7     ivr_dos7;
		} ivr_version;
};
#pragma pack(pop)

#endif
