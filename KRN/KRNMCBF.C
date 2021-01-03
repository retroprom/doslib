
#include <krn/krn.h>
#include <krn/dos.h>

krn_mcb_t krn_mcb_find_seg(seg_t seg) {
	bool_t umblink;
	krn_mcb_t mcb, nextmcb;

	/* enable UMB link if possible */
	umblink = krn_umbl_get();
	if(!umblink) {
		krn_umbl_set(TRUE);
	}

	/* search the MCB chain */
	mcb = krn_mcb_get_first();
	while(mcb) {
		/* check if SEG is before MCB */
		if(mcb > seg) {
			mcb = 0;
			break;
		}
		/* find next MCB in chain */
		nextmcb = krn_mcb_get_next(mcb);
		/* check if SEG is in current MCB */
		if(seg < nextmcb) {
			break;
		}
		/* continue with next MCB */
		mcb = nextmcb;
	}

	/* restore UMB link state */
	if(!umblink) {
		krn_umbl_set(umblink);
	}

	/* return result */
	return mcb;
}
