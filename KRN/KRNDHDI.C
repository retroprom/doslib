
#include <krn/krn.h>
#include <krn/dos.h>

krn_dhd_t krn_dhd_get_first(void) {
	KRN_IVR_VERSION_DECL(ivr4p,dos4plus);
	return &ivr4p->ivr_nul_dhd;
}

krn_dhd_t krn_dhd_get_next(krn_dhd_t d) {
	if(KRN_DHD_IS_LAST(d)) {
		return 0;
	} else {
		return d->dhd_next;
	}
}
