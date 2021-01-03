#ifndef KRN_MCBDEF_H
#define KRN_MCBDEF_H

#define KRN_MCB_PTR(mcb) ((krn_mcb_ptr)MK_FP(mcb,0))

#define KRN_MCB_FLAG_MORE ((byte_t)'M')
#define KRN_MCB_FLAG_LAST ((byte_t)'Z')

#pragma pack(push,1)
struct krn_mcb {
	/*00*/ byte_t mcb_flag;
	/*01*/ word_t mcb_psp;
	/*03*/ word_t mcb_size;
	/*05*/ byte_t _mcb_reserved[3];
	/*08*/ char   mcb_owner[8];
	/*10*/ /* mcb must be 1p long */
};
#pragma pack(pop)

#endif
