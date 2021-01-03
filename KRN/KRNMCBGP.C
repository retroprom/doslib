
#include <krn/krn.h>
#include <krn/dos.h>

krn_psp_t krn_mcb_get_psp(krn_mcb_t m) {
	krn_mcb_ptr mcb = KRN_MCB_PTR(m);
	word_t p = mcb->mcb_psp;
	if(p == 0 || p == 8) {
		return 0;
	}
	return (krn_psp_t)p;
}
