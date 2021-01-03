#ifndef DOSLIB_KRN_DPBDEF_H
#define DOSLIB_KRN_DPBDEF_H

#include <krn/dosdhd.h>

#pragma pack(push,1)
struct krn_dpb {
	/*00*/ byte_t  dpb_num;
	/*01*/ byte_t  dpb_unit;
	/*02*/ word_t  dpb_secsize;
	/*04*/ byte_t  dpb_clulimit;
	/*05*/ byte_t  dpb_clushift;
	/*06*/ word_t  dpb_ressec;
	/*08*/ byte_t  dpb_numfat;
	/*09*/ word_t  dpb_nument;
	/*0B*/ word_t  dpb_firstusrsec;
	/*0D*/ word_t  dpb_clumax;
	/*0F*/ byte_t  dpb_fatsize;
	/*10*/ word_t  dpb_firstdirsec;
	/*12*/ struct krn_dhd far *dpb_dhd;
	/*16*/ byte_t  dpb_mdb;
	/*17*/ byte_t  dpb_flags;
	/*18*/ struct krn_dpb far *dpb_next;
};
#pragma pack(pop)

#endif
