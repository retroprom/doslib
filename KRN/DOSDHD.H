#ifndef DOSLIB_KRN_DHDDEF_H
#define DOSLIB_KRN_DHDDEF_H

#define DHD_ATTR_IS_CHR         0x8000
#define DHD_ATTR_SUP_IOCTL      0x4000
#define DHD_ATTR_SUP_MEDIA      0x0800
#define DHD_ATTR_SUP_IOCTL_CHK  0x0080
#define DHD_ATTR_SUP_IOCTL_GEN  0x0040

#define DHD_ATTR_CHR_SUP_OUTBSY 0x2000
#define DHD_ATTR_CHR_RESERVED5  0x1000
#define DHD_ATTR_CHR_RESERVED4  0x0400
#define DHD_ATTR_CHR_RESERVED3  0x0200
#define DHD_ATTR_CHR_RESERVED2  0x0100
#define DHD_ATTR_CHR_RESERVED1  0x0020
#define DHD_ATTR_CHR_IS_SPECIAL 0x0010
#define DHD_ATTR_CHR_IS_CLOCK   0x0008
#define DHD_ATTR_CHR_IS_NUL     0x0004
#define DHD_ATTR_CHR_IS_STDOUT  0x0002
#define DHD_ATTR_CHR_IS_STDIN   0x0001

#define DHD_ATTR_BLK_IS_NONIBM  0x2000
#define DHD_ATTR_BLK_IS_NETWORK 0x1000
#define DHD_ATTR_BLK_RESERVED6  0x0400
#define DHD_ATTR_BLK_UNKNOWN2   0x0200
#define DHD_ATTR_BLK_UNKNOWN1   0x0100
#define DHD_ATTR_BLK_RESERVED5  0x0020
#define DHD_ATTR_BLK_RESERVED4  0x0010
#define DHD_ATTR_BLK_RESERVED3  0x0008
#define DHD_ATTR_BLK_RESERVED2  0x0004
#define DHD_ATTR_BLK_IS_LBA     0x0002
#define DHD_ATTR_BLK_RESERVED1  0x0001

#define KRN_DHD_IS_LAST(dhd) \
	(FP_OFF(dhd->dhd_next) == 0xFFFF)

#define KRN_DHD_IS_BLK(dhd) \
	(dhd->dhd_attr & DHD_ATTR_IS_CHR)
#define KRN_DHD_IS_CHR(dhd) \
	(dhd->dhd_attr & DHD_ATTR_IS_CHR)

#define KRN_DHD_IS_ATTR(dhd,attr) \
	((dhd->dhd_attr & DHD_ATTR_ ## attr)?TRUE:FALSE)

#define KRN_DHD_IDENT_BLK(dhd) \
	dhd->dhd_ident.dhd_blk
#define KRN_DHD_IDENT_CHR(dhd) \
	dhd->dhd_ident.dhd_chr

/* Reference to type-specific DHD structure
 */
#define KRN_DHD_TYPE_REF(dhd,type) \
	dhd->dhd_type.dhd_##type
/* Get pointer to type-specific DHD structure
 */
#define KRN_DHD_TYPE_PTR(dhd,type) \
	(&dhd->dhd_type.dhd_##type)
/* Declare pointer to type-specific DHD structure
 */
#define KRN_DHD_TYPE_DECL(name,dhd,type) \
	struct krn_dhd_##type far *name = \
		KRN_DHD_TYPE_PTR(dhd,type)

#pragma pack(push,1)
/* Identity structure for character drivers */
struct krn_dhd_chr {
	/*0A*/ byte_t  chr_name[8];
	/*12*/
};
/* Identity structure for block drivers */
struct krn_dhd_blk {
	/*0A*/ byte_t  blk_numunits;
	/*0B*/ byte_t  blk_ident[7];
	/*12*/
};
/* Type-specific structure for CD-ROM drives */
struct krn_dhd_cdr {
	/*12*/ word_t  cdr_chain;
	/*14*/ byte_t  cdr_drive;
	/*15*/ byte_t  cdr_numunits;
	/*16*/ byte_t  cdr_ident[6];
	/*1C*/
};
/* Generalized DHD structure */
struct krn_dhd {
	/*00*/ struct krn_dhd far *dhd_next;
	/*04*/ word_t  dhd_attr;
	/*06*/ word_t  dhd_strat_off;
	/*08*/ word_t  dhd_int;
	/*0A*/
		union {
			struct krn_dhd_chr dhd_chr;
			struct krn_dhd_blk dhd_blk;
		} dhd_ident;
	/*12*/
		union {
			struct krn_dhd_cdr dhd_cdrom;
		} dhd_type;
};
#pragma pack(pop)

#endif
