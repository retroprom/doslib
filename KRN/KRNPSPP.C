
#include <krn/krn.h>
#include <krn/dos.h>

krn_psp_t krn_psp_get_parent(krn_psp_t psp) {
	krn_psp_ptr p = KRN_PSP_PTR(psp);
	if(KRN_PSP_IS_TOP(psp)) {
		return 0;
	} else {
		return p->psp_parent;
	}
}
