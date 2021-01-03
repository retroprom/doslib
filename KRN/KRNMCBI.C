
#include <krn/krn.h>
#include <krn/dos.h>

krn_mcb_t krn_mcb_get_first(void) {
	return krn_ivr->ivr_first_mcb;
}

krn_mcb_t krn_mcb_get_next(krn_mcb_t m) {
	krn_mcb_ptr mcb = KRN_MCB_PTR(m);
	if(mcb->mcb_flag == KRN_MCB_FLAG_LAST) {
		return 0;
	}
	return m + mcb->mcb_size + 1;
}
